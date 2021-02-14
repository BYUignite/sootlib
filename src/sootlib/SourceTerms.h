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

	[[nodiscard]] double getGasSourceTerm(size_t i) const
	{
		return gasSourceTerms.at(i);
	}
	void setGasSourceTerm(size_t i, double value)
	{
		gasSourceTerms.at(i) = value;
	}
	[[nodiscard]] size_t getNumGasSourceTerms() const
	{
		return gasSourceTerms.size();
	}

private:
	std::vector<double> sootSourceTerms;
	std::vector<double> gasSourceTerms;
};
}

#endif //SOURCETERMS_H
