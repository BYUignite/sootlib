#ifndef SOOTSOURCETERMS_H
#define SOOTSOURCETERMS_H

#include <utility>
#include <vector>

namespace soot
{
class SootSourceTerms
{
public:
	/* Constructor */

	explicit SootSourceTerms(std::vector<double> sourceTerms)
	{
		this->sourceTerms = std::move(sourceTerms);
	}

	/* Getters and setters */

	[[nodiscard]] double getSourceTerm(size_t i) const
	{
		return sourceTerms.at(i);
	}
	void setSourceTerm(size_t i, double value)
	{
		sourceTerms.at(i) = value;
	}
	[[nodiscard]] size_t getNumSourceTerms() const
	{
		return sourceTerms.size();
	}

private:
	std::vector<double> sourceTerms;
};
}

#endif //SOOTSOURCETERMS_H
