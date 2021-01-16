#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "game.h"
#include "physical_object.h"
#include "debug.h"

namespace Game_Objects{
    extern int const TICKS_PER_SECOND,
                     TICKS_TIME,
                     MAX_FRAMESKIP;

    Ball_List balls;

    XY Physical_Object::getMove(){
        if (key){
            switch(players[key].get_Direction()){
                case UPPER_LEFT:
                    return to_XY(-1/sqrt(2), -1/sqrt(2));
                case UP:
                    return to_XY(0, -1);
                case UPPER_RIGHT:
                    return to_XY(1/sqrt(2), -1/sqrt(2));
                case LEFT:
                    return to_XY(-1, 0);
                case MIDDLE:
                    return to_XY(0, 0);
                case RIGHT:
                    return to_XY(1, 0);
                case LOWER_LEFT:
                    return to_XY(-1/sqrt(2), 1/sqrt(2));
                case DOWN:
                    return to_XY(0, 1);
                case LOWER_RIGHT:
                    return to_XY(1/sqrt(2), 1/sqrt(2));
                default:
                    return to_XY(0, 0);
            }
        } else {
            return to_XY(0, 0);
        }
    }

    void Physical_Object::update_position(){  // x' := x + vΔt
        pos += vel * TICKS_INTERVEL;
    }

    void Physical_Object::move(){
        XY movement = getMove();

        if (accelerative_Mode){
            vel += acc_v * movement;
        } else {
            if (movement==last_movement){
                if (movement.x || movement.y){
                    XY vel_od = rotation(vel, movement.x, movement.y);
DEBUG_output_set(std::cout<< "ID: "<< (int)this-(int)&*balls.list_balls.begin()<< "; update_velocity: "<< movement<< "; ";)
                    if (vel_od.x < 0){
                        vel_od.x = std::min(move_v, vel_od.x + move_v);
DEBUG_output_set(std::cout<< "vel_p <  0; ";)
                    } else if (vel_od.x < move_v){
                        vel_od.x = std::min(move_v, vel_od.x + move_v);
DEBUG_output_set(std::cout<< "vel_p < +m; ";)
                    } else {
DEBUG_output_set(std::cout<< "vel_p >= +m; ";)
                    }
                    if (vel_od.y < 0){
                        vel_od.y = std::min(0.0, vel_od.y + dec_v);
DEBUG_output_set(std::cout<< "vel_h <  0; ";)
                    } else if (vel_od.y > 0){
                        vel_od.y = std::max(0.0, vel_od.y - dec_v);
DEBUG_output_set(std::cout<< "vel_h >  0; ";)
                    } else {
DEBUG_output_set(std::cout<< "vel_h =  0; ";)
                    }
                    vel = rotation(vel_od, movement.x, -movement.y);
DEBUG_output_set(std::cout<< "vel_od: "<< vel_od<< "; vel: "<< vel<< "; pos: "<< pos<< std::endl;)
                }
            } else {
                if (last_movement.x || last_movement.y){
                    XY vel_od = rotation(vel, last_movement.x, last_movement.y),
                       move_differ = to_XY(inner_product(movement, last_movement), inner_product(movement, rotation(last_movement, 0, 1)));
DEBUG_output_set(std::cout<< "ID: "<< (int)this-(int)&*balls.list_balls.begin()<< "; update_velocity: "<< movement<< "; ";)
                    if (vel_od.x < -move_v){
                        if (move_differ.x>=0){
                            vel_od.x = std::min(0.0, vel_od.x + move_v);
                        }
DEBUG_output_set(std::cout<< "vel_p (last_move) < -m; ";)
                    } else if (vel_od.x < 0){
                        vel_od.x = std::min(0.0, vel_od.x + move_v);
DEBUG_output_set(std::cout<< "vel_p (last_move) <  0; ";)
                    } else if (vel_od.x > move_v){
                        if (move_differ.x<=0){
                            vel_od.x = std::max(0.0, vel_od.x - move_v);
                        }
DEBUG_output_set(std::cout<< "vel_p (last_move) > +m; ";)
                    } else if (vel_od.x > 0){
                        vel_od.x = std::max(0.0, vel_od.x - move_v);
DEBUG_output_set(std::cout<< "vel_p (last_move) >  0; ";)
                    } else {
DEBUG_output_set(std::cout<< "vel_p (last_move) =  0; ";)
                    }
                    if (vel_od.y < -move_v){
                        if (move_differ.y>=0){
                            vel_od.y = std::min(0.0, vel_od.y + dec_v);
                        }
DEBUG_output_set(std::cout<< "vel_h (last_move) < -m; ";)
                    } else if (vel_od.y < 0){
                        vel_od.y = std::min(0.0, vel_od.y + dec_v);
DEBUG_output_set(std::cout<< "vel_h (last_move) <  0; ";)
                    } else if (vel_od.y > move_v){
                        if (move_differ.y<=0){
                            vel_od.y = std::max(0.0, vel_od.y - dec_v);
                        }
DEBUG_output_set(std::cout<< "vel_h (last_move) > +m; ";)
                    } else if (vel_od.y > 0){
                        vel_od.y = std::max(0.0, vel_od.y - dec_v);
DEBUG_output_set(std::cout<< "vel_h (last_move) >  0; ";)
                    } else {
DEBUG_output_set(std::cout<< "vel_h (last_move) =  0; ";)
                    }
                    vel = rotation(vel_od, last_movement.x, -last_movement.y);
DEBUG_output_set(std::cout<< "vel_od (last_move): "<< vel_od<< "; vel: "<< vel<< "; pos: "<< pos<< std::endl;)
                }
                if (movement.x || movement.y){
                    XY vel_od = rotation(vel, movement.x, movement.y);
DEBUG_output_set(std::cout<< "ID: "<< (int)this-(int)&*balls.list_balls.begin()<< "; update_velocity: "<< movement<< "; ";)
                    if (vel_od.x < 0){
                        vel_od.x = std::min(move_v, vel_od.x + move_v);
DEBUG_output_set(std::cout<< "vel_p (move) <  0; ";)
                    } else if (vel_od.x < move_v){
                        vel_od.x = std::min(move_v, vel_od.x + move_v);
DEBUG_output_set(std::cout<< "vel_p (move) < +m; ";)
                    } else {
DEBUG_output_set(std::cout<< "vel_p (move) >= +m; ";)
                    }
                    if (vel_od.y < 0){
                        vel_od.y = std::min(0.0, vel_od.y + dec_v);
DEBUG_output_set(std::cout<< "vel_h (move) <  0; ";)
                    } else if (vel_od.y > 0){
                        vel_od.y = std::max(0.0, vel_od.y - dec_v);
DEBUG_output_set(std::cout<< "vel_h (move) >  0; ";)
                    } else {
DEBUG_output_set(std::cout<< "vel_h (move) =  0; ";)
                    }
                    vel = rotation(vel_od, movement.x, -movement.y);
DEBUG_output_set(std::cout<< "vel_od (move): "<< vel_od<< "; vel: "<< vel<< "; pos: "<< pos<< std::endl;)
                }
            }
        }
        last_movement = movement;
    }

    void Physical_Object::force_to_velocity(){  // F' := F'
        // v = a × t = F / m × t = (Ft) / m = Σ(F) × t / m = Σ(F × t / m)
        for (std::list<Force_Element>::iterator k = fs.begin(), n = fs.end(); k != n;){
            if (k->active_Time <= 0){
                k = fs.erase(k);
                continue;
            }
            if (dist(k->value) > max_acc * mass){
                vel += max_acc * to_XY(cos_of_arg(k->value), sin_of_arg(k->value)) * TICKS_INTERVEL;
            } else {
                vel += k->value / mass * TICKS_INTERVEL;
            }
DEBUG_output_set(std::cout<< "ID: "<< (int)this-(int)&*balls.list_balls.begin()<< "; update_force: "<<
                             k->comment<< ": "<< k->value<< "; vel: "<< vel<< "; pos: "<< pos<< std::endl;)
            -- k->active_Time;
            if (k->active_Time <= 0){k = fs.erase(k);} else {++k;}
        }
    }

    void Ball::collision_Border(){
        if (pos.x < radius){
            pos.x = radius;
            vel = to_XY(-(c_restitution)/2.0*std::min(vel.x, 0.0), vel.y);
DEBUG_output_set(std::cout<< "ID: "<< (int)this-(int)&*balls.list_balls.begin()<< "; collision_Border: "<< "LEFT; vel: "<< vel<< "; pos: "<< pos<< std::endl;)
        }
        if (pos.x > width - radius){
            pos.x = width - radius;
            vel = to_XY(-(c_restitution)/2.0*std::max(vel.x, 0.0), vel.y);
DEBUG_output_set(std::cout<< "ID: "<< (int)this-(int)&*balls.list_balls.begin()<< "; collision_Border: "<< "RIGHT; vel: "<< vel<< "; pos: "<< pos<< std::endl;)
        }
        if (pos.y < radius){
            pos.y = radius;
            vel = to_XY(vel.x, -(c_restitution)/2.0*std::min(vel.y, 0.0));
DEBUG_output_set(std::cout<< "ID: "<< (int)this-(int)&*balls.list_balls.begin()<< "; collision_Border: "<< "UP; vel: "<< vel<< "; pos: "<< pos<< std::endl;)
        }
        if (pos.y > height - radius){
            pos.y = height - radius;
            vel = to_XY(vel.x, -(c_restitution)/2.0*std::max(vel.y, 0.0));
DEBUG_output_set(std::cout<< "ID: "<< (int)this-(int)&*balls.list_balls.begin()<< "; collision_Border: "<< "DOWN; vel: "<< vel<< "; pos: "<< pos<< std::endl;)
        }
    }

    void Ball::display(SDL_Renderer *Renderer, double interpolation){
        filledEllipseRGBA(Renderer, pos.x + (vel.x * TICKS_INTERVEL * (interpolation)), pos.y + (vel.y * TICKS_INTERVEL * (interpolation)),
                          radius, radius, colour.r, colour.g, colour.b, colour.a);
    }

    void Ball_List::update(){
    }

    void Ball_List::display(SDL_Renderer *Renderer, double interpolation){
    }

    void gravitation(Physical_Object &lhs, Physical_Object &rhs){
        XY d;
        double distance,
               cos_th, sin_th,
               Force;

        d = rhs.pos-lhs.pos;
        distance = dist(d);

        if (!d.x && !d.y){
            return;
        } else {
            cos_th = d.x/distance;
            sin_th = d.y/distance;
        }

        Force = (G*lhs.mass*rhs.mass) / (distance / 100.0 * distance / 100.0);

        lhs.fs.push_back(Force_Element(to_XY(Force * cos_th, Force * sin_th), 1, "Gravitation"));
        rhs.fs.push_back(Force_Element(to_XY(-Force * cos_th, -Force * sin_th), 1, "Gravitation Anti-force"));
    }

    void ball_Collision(Ball &lhs, Ball &rhs){
        XY d, v1, v2, c;
        double distance,
               theta, cos_th, sin_th,
               _vp1, _vp2;

        d = rhs.pos-lhs.pos;
        distance = dist(d);

        if (distance >= lhs.radius + rhs.radius){return;}

        if (!d.x && !d.y){
            theta = rand_R_Open(0, 2.0*PI);
            cos_th = cos(theta);
            sin_th = sin(theta);
        } else {
            cos_th = d.x/distance;
            sin_th = d.y/distance;
        }

        v1 = rotation(lhs.vel, cos_th, sin_th);
        v2 = rotation(rhs.vel, cos_th, sin_th);

        _vp1 = (lhs.mass*v1.x + rhs.mass*v2.x + (lhs.c_restitution+rhs.c_restitution)/2.0 *rhs.mass*(v2.x-v1.x))/(lhs.mass+rhs.mass);
        _vp2 = (lhs.mass*v1.x + rhs.mass*v2.x + (lhs.c_restitution+rhs.c_restitution)/2.0 *lhs.mass*(v1.x-v2.x))/(lhs.mass+rhs.mass);

        c = to_XY((lhs.pos.x*lhs.mass + rhs.pos.x*rhs.mass),
                  (lhs.pos.y*lhs.mass + rhs.pos.y*rhs.mass)) / (lhs.mass + rhs.mass);

        lhs.pos = to_XY(c.x - (rhs.mass*(lhs.radius+rhs.radius) / (lhs.mass+rhs.mass)*cos_th),
                        c.y - (rhs.mass*(lhs.radius+rhs.radius) / (lhs.mass+rhs.mass)*sin_th));
        rhs.pos = to_XY(c.x + (lhs.mass*(lhs.radius+rhs.radius) / (lhs.mass+rhs.mass)*cos_th),
                        c.y + (lhs.mass*(lhs.radius+rhs.radius) / (lhs.mass+rhs.mass)*sin_th));

        lhs.vel = rotation(to_XY(_vp1, v1.y), cos_th, -sin_th);
        rhs.vel = rotation(to_XY(_vp2, v2.y), cos_th, -sin_th);

DEBUG_output_set(std::cout<< "ID: "<< (int)&lhs-(int)&*balls.list_balls.begin()<< "; ball_Collision"<< "; vel: "<< lhs.vel<< "; pos: "<< lhs.pos<< std::endl;)
DEBUG_output_set(std::cout<< "ID: "<< (int)&rhs-(int)&*balls.list_balls.begin()<< "; ball_Collision Anti-force"<< "; vel: "<< rhs.vel<< "; pos: "<< rhs.pos<< std::endl;)
    }

    void ball_Magic_Collision(Ball &lhs, Ball &rhs){
        XY d, v1, v2;
        double distance,
               theta, cos_th, sin_th,
               _vp1, _vp2;

        d = rhs.pos-lhs.pos;
        distance = dist(d);

        if (!d.x && !d.y){
            theta = rand_R_Open(0, 2.0*PI);
            cos_th = cos(theta);
            sin_th = sin(theta);
        } else {
            cos_th = d.x/distance;
            sin_th = d.y/distance;
        }

        v1 = rotation(lhs.vel, cos_th, sin_th);
        v2 = rotation(rhs.vel, cos_th, sin_th);

        _vp1 = (lhs.mass*v1.x + rhs.mass*v2.x + rhs.mass*(v2.x-v1.x))/(lhs.mass+rhs.mass);
        _vp2 = (lhs.mass*v1.x + rhs.mass*v2.x + lhs.mass*(v1.x-v2.x))/(lhs.mass+rhs.mass);

        lhs.vel = rotation(to_XY(_vp1, v1.y), cos_th, -sin_th);
        rhs.vel = rotation(to_XY(_vp2, v2.y), cos_th, -sin_th);

DEBUG_output_set(std::cout<< "ID: "<< (int)&lhs-(int)&*balls.list_balls.begin()<< "; ball_Magic_Collision"<< "; vel: "<< lhs.vel<< "; pos: "<< lhs.pos<< std::endl;)
DEBUG_output_set(std::cout<< "ID: "<< (int)&lhs-(int)&*balls.list_balls.begin()<< "; ball_Magic_Collision Anti-force"<< "; vel: "<< rhs.vel<< "; pos: "<< rhs.pos<< std::endl;)
    }
}