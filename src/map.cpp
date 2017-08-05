#include "map.h"

using namespace std;
using namespace tk; // spline

Map::Map(string map_file_) {

  vector<double> map_waypoints_x;
  vector<double> map_waypoints_y;
  vector<double> map_waypoints_s;
  vector<double> map_waypoints_dx;
  vector<double> map_waypoints_dy;

  ifstream in_map_(map_file_.c_str(), ifstream::in);

  string line;
  while (getline(in_map_, line)) {
    istringstream iss(line);
    double x;
    double y;
    float s;
    float d_x;
    float d_y;
    iss >> x;
    iss >> y;
    iss >> s;
    iss >> d_x;
    iss >> d_y;
    map_waypoints_x.push_back(x);
    map_waypoints_y.push_back(y);
    map_waypoints_s.push_back(s);
    map_waypoints_dx.push_back(d_x);
    map_waypoints_dy.push_back(d_y);
  }

  // set points
  this->wp_spline_x.set_points(map_waypoints_s, map_waypoints_x);
  this->wp_spline_y.set_points(map_waypoints_s, map_waypoints_y);
  this->wp_spline_dx.set_points(map_waypoints_s, map_waypoints_dx);
  this->wp_spline_dy.set_points(map_waypoints_s, map_waypoints_dy);

}

vector<double> Map::getXY(double mod_s){
  double wp_x, wp_y, wp_dx, wp_dy, next_x, next_y;

  // spline interpolation
  wp_x = this->wp_spline_x(mod_s);
  wp_y = this->wp_spline_y(mod_s);
  wp_dx = this->wp_spline_dx(mod_s);
  wp_dy = this->wp_spline_dy(mod_s);

  next_x = roundf((wp_x + wp_dx * 6.0)*100) / 100;
  next_y = roundf((wp_y + wp_dy * 6.0)*100) / 100;

  return {next_x, next_y};
}