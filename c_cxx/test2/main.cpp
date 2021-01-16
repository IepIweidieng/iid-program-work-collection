#include <iostream>
#include <string>

int main(){
    std::string S_club, S_quality;
    auto Are_you = [&](std::string aspect)
            {return S_quality == aspect;},
         &Do_you = Are_you;

    std::cin >> S_club;

    while (S_club == "nlpc")
        std::cin  >> S_quality,
        std::cout << (
              Are_you ("outstanding")?
                "GO AHEAD"
            : Are_you ("worthless")?
                "YOUTH IS WASTED"
            :  Do_you ("program")?
                "NLPC WELCOMES YOU!!"
            : ("Are all the above", false?
                "If so, ":
                "BACK TO YOUR KENNEL")
        ) << '\n';

    std::cerr << "401 NOT FOUND" << '\n';

    return 0;
}
