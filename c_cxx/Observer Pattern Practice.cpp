/* Observer Pattern Practice
Written by Iweidieng Iep on 2019-05-23

Demonstration of basic observer pattern.
*/

#include <iostream>
#include <string>
#include <utility>
#include <unordered_set>

template <typename... Ts>
  using List = std::unordered_set<Ts...>;

template <typename... Info_Ts>
 class Observer {
  public:
    virtual void update(Info_Ts... infos) = 0;
};

template <typename Observer_T, typename... Info_Ts>
 class Subject {
  public:
    virtual void register_observer(Observer_T& obs)
      { list_.emplace(&obs); }
    virtual void unregister_observer(Observer_T& obs)
      { list_.erase(&obs); }
    virtual void notify_observers(Info_Ts... infos) = 0;

  protected:
    List<Observer_T*> list_;
};


class User;
List<User*> everyone;

class User : public Observer<const std::string&> {
  public:
    User(const std::string& name): name_ {name}
      { everyone.emplace(this); }

    virtual void update(const std::string& info) override
    {
        std::cout << "User " << name_ << " received '" << info << "'.\n";
    }

    ~User()  { everyone.erase(this); }

  protected:
    std::string name_;
};

class Uploader : public Subject<User, const std::string&>, public virtual User {
  public:
    Uploader(const std::string& name) : User{name} { }

    void update(const std::string& info) override
    {
        std::cout << "Uploader " << name_ << " received '" << info << "'.\n";
    }

    void notify_observers(const std::string& info) override
    {
        for (auto v: list_) {
            v->update(name_ + " uploaded a new vid: " + info);
        }
    }
};


List<User*> operator and(User& lhs, User& rhs)
  { return {&lhs, &rhs}; }
auto operator and(List<User*>& lhss, User& rhs) -> decltype(lhss)
{
    lhss.emplace(&rhs);
    return lhss;
}

List<Uploader::Subject*> operator and(Uploader& lhs, Uploader& rhs)
  { return {&lhs, &rhs}; }
auto operator and(List<Uploader::Subject*>& lhss, Uploader& rhs) -> decltype(lhss)
{
    lhss.emplace(&rhs);
    return lhss;
}


template <typename Lhs, typename Rhs, void (Rhs::*meth)(Lhs&)>
 struct Meth_opr {
    friend Meth_opr operator*(Lhs& lhs, const Meth_opr& opr)
    {
        return std::move(List<Lhs*>{&lhs} * opr);
    }
    friend Meth_opr operator*(const List<Lhs*>& lhss, const Meth_opr& opr)
    {
        for (auto v: lhss) {
            for (auto u: opr.rhss_) {
                (u->*meth)(*v);
            }
        }
        Meth_opr res {opr};
        res.lhss_.insert(lhss.begin(), lhss.end());
        return std::move(res);
    }

    Meth_opr operator*(Rhs& rhs)
    {
        return std::move(*this * List<Rhs*>{&rhs});
    }
    Meth_opr operator*(const List<Rhs*>& rhss)
    {
        for (auto u: rhss) {
            for (auto v: lhss_) {
                (u->*meth)(*v);
            }
        }
        Meth_opr res {*this};
        res.rhss_.insert(rhss.begin(), rhss.end());
        return std::move(res);
    }

    friend Meth_opr operator and(Lhs& lhs, const Meth_opr& opr)
      { return std::move(lhs * opr); }
    friend Meth_opr operator and(const List<Lhs*>& lhss, const Meth_opr& opr)
      { return std::move(lhss * opr); }
    Meth_opr operator and(Rhs& rhs)
      { return std::move(*this * rhs); }
    Meth_opr operator and(const List<Rhs*>& rhss)
      { return std::move(*this * rhss); }

    List<Lhs*> lhss_;
    List<Rhs*> rhss_;
};

template <void (Uploader::Subject::*meth)(User&)>
  using Uploader_meth_opr = Meth_opr<User, Uploader::Subject, meth>;
auto subscript_to = Uploader_meth_opr<&Uploader::register_observer>{};
auto unsubscript_to = Uploader_meth_opr<&Uploader::unregister_observer>{};

template <void (Uploader::Subject::*meth)(User&)>
  Uploader_meth_opr<meth> operator *(
      const List<Uploader::Subject*>& lhss, const Uploader_meth_opr<meth>& opr)
{
    List<User*> tmp;
    for (auto v: lhss) {
        tmp.emplace(dynamic_cast<Uploader*>(v));
    }
    return std::move(tmp * opr);
}

auto uploaded_by = Meth_opr<const std::string, Uploader, &Uploader::notify_observers>{};

int main()
{
    auto pewd {Uploader{"pewd"}};
    auto tsr {Uploader{"T-sr"}};
    auto justy {User{"JustY"}};

    std::cout << "Test 1:" "\n";

    justy *subscript_to* pewd and tsr;
    pewd *subscript_to* tsr;

    "subscript to tsr" *uploaded_by* pewd;
    "pls subscript" *uploaded_by* tsr;

    std::cout << "\n"
      "Test 2:" "\n";

    justy *unsubscript_to* tsr and pewd;
    tsr and pewd *subscript_to* pewd;

    "congrat" *uploaded_by* pewd;
    "test" and "test 2" *uploaded_by* tsr;

    std::cout << "\n"
      "Test 3:" "\n";

    everyone *subscript_to* pewd;

    "hi everone" and "test 3"
      *uploaded_by* pewd and tsr;
}