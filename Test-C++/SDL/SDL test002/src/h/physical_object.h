#ifndef PHYSICAL_OBJECT_H_INCLUDED
#define PHYSICAL_OBJECT_H_INCLUDED


#include <iostream>
#include <vector>
#include "keymap.h"
#include "coordinate.h"

namespace Game_Objects{
    struct Force_Element{
        XY value;
        Uint32 active_Time;
        std::string comment;

        Force_Element(XY _value, Uint32 _active_Time, std::string _comment = ""):
          value (_value), active_Time (_active_Time), comment(_comment){}

        friend std::ostream &operator<<(std::ostream &lhs, Force_Element const &rhs){
            std::cout<< "Force: "<< rhs.value<< "; Life: "<< rhs.active_Time<< "; Comment: "<< rhs.comment;
            return lhs;
        }
    };

    struct Physical_Object{
        size_t key;
        XY pos,
           vel,
           last_movement;
        double mass,
               move_v,
               acc_v,
               dec_v;
        std::list <Force_Element> fs;

        Physical_Object(XY _pos, XY _vel, double _mass, double _move_v, double _acc_v, double _dec_v):
          key (), pos(_pos), vel (_vel), last_movement (),
          mass (_mass), move_v (_move_v), acc_v (_acc_v), dec_v (_dec_v), fs (){}

        Physical_Object(Physical_Object const &rhs):
          key (rhs.key), pos(rhs.pos), vel (rhs.vel), last_movement (rhs.last_movement),
          mass (rhs.mass), move_v (rhs.move_v), acc_v (rhs.acc_v), dec_v (rhs.dec_v), fs (rhs.fs){}

        ~Physical_Object(){fs.clear();}

        void bind_to_key(size_t _key){key = _key;}

        XY getMove();
        void update_position();
        void move();
        void force_to_velocity();

      private:
        Physical_Object &operator=(Physical_Object const&);
    };

    struct Ball: public Physical_Object{
      friend class Ball_List;
        RGBA colour;
        double c_restitution, radius;

        Ball(XY _pos, XY _v, double _m, double _move_v, double _acc_v, double _dec_v, RGBA _colour, double _c_restitution, double _radius):
          Physical_Object(_pos, _v, _m, _move_v, _acc_v, _dec_v),
          colour (_colour), c_restitution (_c_restitution), radius (_radius){}

        Ball(Ball const &rhs):
          Physical_Object(rhs),
          colour (rhs.colour), c_restitution (rhs.c_restitution), radius (rhs.radius){}

        void collision_Border();
        void display(SDL_Renderer *Renderer, double interpolation);
    };

    struct Ball_List{
        std::vector<Ball> list_balls;

        Ball_List():
          list_balls(){}

        void update();
        void display(SDL_Renderer *Renderer, double interpolation);
    };

    void gravitation(Physical_Object &lhs, Physical_Object &rhs);
    void ball_Collision(Ball &lhs, Ball &rhs);
    void ball_Magic_Collision(Ball &lhs, Ball &rhs);

    extern Ball_List balls;
}

#endif // PHYSICAL_OBJECT_H_INCLUDED
