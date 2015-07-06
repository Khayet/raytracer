#include "material.hpp"

		Material::Material(Color ka,Color  kd, Color  ks) 
		: name_{}, ka_{ka}, kd_{kd}, ks_{ks}, m_{0} {
		}
		Material::Material(Color ka,Color  kd, Color  ks, float m) 
		: name_{}, ka_{ka}, kd_{kd}, ks_{ks}, m_{m} {
		}
		Material::Material() : name_{}, ka_{0.0, 0.0, 0.0}, kd_{0.0,0.0,0.0}, ks_{0.0,0.0,0.0}, m_{0} {
		};
		Material::Material(std::string name, Color ka,Color  kd, Color  ks, float m) 
		: name_{name}, ka_{ka}, kd_{kd}, ks_{ks}, m_{m} {
		}

		/* virtual */ std::ostream& Material::print(std::ostream& os) const {
			os << "\n";
			os << "Material \"" << name_ << "\" : \n";
			os << "  name    :  " << name_ << "\n";
			os << "  colorka   :  " << ka_;
			os << "  colorkd   :  " << kd_;
			os << "  colorks   :  " << ks_;
			os << "  m   :  " << m_;
			
			return os;
		}
		std::string Material::name() const { return name_; }
		Color Material::color_ka()const { return ka_; }
		Color Material::color_kd()const { return kd_; }
		Color Material::color_ks()const { return ks_; }
		float Material::m() const { return m_; }
	

std::ostream& operator<<(std::ostream &os, Material const& m)
{
  return m.print(os);
}
