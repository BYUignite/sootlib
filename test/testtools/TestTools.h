#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include <memory>

#include "sootlib/state/gas/State.h"
#include "sootlib/state/soot/MomentSootState.h"
#include "sootlib/state/soot/BinSootState.h"
#include "sootlib/soot_models/bin/BinSootModel.h"
#include "sootlib/soot_model/generator/BinSootModelGenerator.h"
#include "sootlib/soot_models/moment/MomentSootModel.h"
#include "sootlib/soot_model/generator/MomentSootModelGenerator.h"

class TestTools
{
public:
	[[nodiscard]] static soot::State getBlankGasState()
	{
		return soot::State();
	}

	[[nodiscard]] static soot::MomentSootState getBlankMomentSootState()
	{
		return soot::MomentSootState();
	}

	[[nodiscard]] static soot::BinSootState getBlankBinSootState()
	{
		return soot::BinSootState();
	}
	
	[[nodiscard]] static soot::BinSootModel* getDefaultBinSootModel()
	{
		auto generator = soot::BinSootModelGenerator();
		return generator.getModel();
	}
	
	[[nodiscard]] static std::unique_ptr<soot::BinSootModel> getDefaultBinSootModelUnique()
	{
		auto generator = soot::BinSootModelGenerator();
		return generator.getModelUnique();
	}
	
	[[nodiscard]] static std::shared_ptr<soot::BinSootModel> getDefaultBinSootModelShared()
	{
		auto generator = soot::BinSootModelGenerator();
		return generator.getModelShared();
	}

	[[nodiscard]] static soot::MomentSootModel* getDefaultMomentSootModel()
	{
		auto generator = soot::MomentSootModelGenerator();
		return generator.getModel();
	}

	[[nodiscard]] static std::unique_ptr<soot::MomentSootModel> getDefaultMomentSootModelUnique()
	{
		auto generator = soot::MomentSootModelGenerator();
		return generator.getModelUnique();
	}

	[[nodiscard]] static std::shared_ptr<soot::MomentSootModel> getDefaultMomentSootModelShared()
	{
		auto generator = soot::MomentSootModelGenerator();
		return generator.getModelShared();
	}
};

#endif //TESTTOOLS_H
