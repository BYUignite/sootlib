#ifndef SOURCETERMS_H
#define SOURCETERMS_H

#include <utility>
#include <vector>

namespace soot
{
class SourceTerms
{
public:
	/* Constructor */

	explicit SourceTerms(std::vector<double> sootSourceTerms, std::vector<double> gasSourceTerms)
	{
		this->sootSourceTerms = std::move(sootSourceTerms);
		this->gasSourceTerms = std::move(gasSourceTerms);
	}

	/* Getters and setters */

	[[nodiscard]] double getSootSourceTerm(size_t i) const
	{
		return sootSourceTerms.at(i);
	}
	void setSootSourceTerm(size_t i, double value)
	{
		sootSourceTerms.at(i) = value;
	}
	[[nodiscard]] size_t getNumSootSourceTerms() const
	{
		return sootSourceTerms.size();
	}

	[[nodiscard]] double getC2H2Src() const
	{
		return C2H2_src;
	}
	void setC2H2Src(double c2H2Src)
	{
		C2H2_src = c2H2Src;
	}
	[[nodiscard]] double getO2Src() const
	{
		return O2_src;
	}
	void setO2Src(double o2Src)
	{
		O2_src = o2Src;
	}
	[[nodiscard]] double getHSrc() const
	{
		return H_src;
	}
	void setHSrc(double hSrc)
	{
		H_src = hSrc;
	}
	[[nodiscard]] double getH2Src() const
	{
		return H2_src;
	}
	void setH2Src(double h2Src)
	{
		H2_src = h2Src;
	}
	[[nodiscard]] double getOhSrc() const
	{
		return OH_src;
	}
	void setOhSrc(double ohSrc)
	{
		OH_src = ohSrc;
	}
	[[nodiscard]] double getH2OSrc() const
	{
		return H2O_src;
	}
	void setH2OSrc(double h2OSrc)
	{
		H2O_src = h2OSrc;
	}
	[[nodiscard]] double getCoSrc() const
	{
		return CO_src;
	}
	void setCoSrc(double coSrc)
	{
		CO_src = coSrc;
	}
	[[nodiscard]] double getElementalCSrc() const
	{
		return elementalC_src;
	}
	void setElementalCSrc(double elementalCSrc)
	{
		elementalC_src = elementalCSrc;
	}
	[[nodiscard]] double getElementalHSrc() const
	{
		return elementalH_src;
	}
	void setElementalHSrc(double elementalHSrc)
	{
		elementalH_src = elementalHSrc;
	}

private:
	std::vector<double> sootSourceTerms;

	/* Gas Source Terms */
	double C2H2_src;
	double O2_src;
	double H_src;
	double H2_src;
	double OH_src;
	double H2O_src;
	double CO_src;
	double elementalC_src;
	double elementalH_src;
};
}

#endif //SOURCETERMS_H
