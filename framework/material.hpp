#ifndef MATERIAL_HPP
#define MATERIAL_HPP
//
#include "color.hpp"

#include <string>

class Material{
	public:
		Material(Color ka, Color kd, Color ks);
		Material(Color ka, Color kd, Color ks, float m);
		Material();
		Material(std::string name, Color ka, Color kd, Color ks, float m);
		Material(Material const& copy_material);

		/* virtual */ std::ostream& print(std::ostream& os) const;
		std::string name() const;
		Color color_ka() const;
		Color color_kd() const;
		Color color_ks() const;
		float m() const;

	private:
		std::string name_;
		Color ka_;
		Color kd_;
		Color ks_;
		float m_;
	}; 

std::ostream& operator<<(std::ostream &os, Material const& m);

#endif 
