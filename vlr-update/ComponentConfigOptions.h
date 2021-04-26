#pragma once

#include <optional>

#include <boost/program_options.hpp>

#include <vlr-util/cpp_namespace.h>
#include <vlr-util/ModuleContext.Runtime.ConfigOptionsBase.h>

class CComponentConfigOptions
	: public vlr::ModuleContext::Runtime::CConfigOptionsBase
{
public:
	std::optional<bool> m_obInstallService;
	std::optional<bool> m_obRemoveService;
	std::optional<cpp::tstring> m_osServiceName;

};
