#pragma once

#include <chrono>

#include <vlr-util/zstring_view.h>
#include <vlr-util/ModuleContext.Runtime.CommandLine.h>

#include "ComponentConfigOptions.h"

class CComponentConfigOptionsManager
{
protected:
	struct CConfigOptionsAndPopulationInfo
	{
		CComponentConfigOptions m_oComponentConfigOptions;
		std::optional<std::chrono::time_point<std::chrono::system_clock>> m_odtPopulationTime_CommandLine;

		bool IsPopulated() const
		{
			return m_odtPopulationTime_CommandLine.has_value();
		}
	};

public:
	HRESULT PopulateConfigOptions();
protected:
	HRESULT PopulateConfigOptionsMapping();
	HRESULT PopulateConfigOptions_ViaCommandLine( const vlr::ModuleContext::Runtime::CCommandLine& oCommandLine );
	HRESULT PopulateConfigOptions_ViaCommandLine_Implicit();

public:
	const CComponentConfigOptions& GetPopulatedOptions();

protected:
	static CConfigOptionsAndPopulationInfo& GetSharedComponentOptions();

protected:
	static const boost::program_options::options_description& GetOptionsDesc_All();

public:
	static constexpr vlr::zstring_view m_svzOptionName_Help = "help";
	static constexpr vlr::zstring_view m_svzOptionDescription_Help =
		"show available options";

	static constexpr vlr::zstring_view m_svzOptionName_InstallService = "install-service";
	static constexpr vlr::zstring_view m_svzOptionDescription_InstallService =
		"install the component as a Windows service";

	static constexpr vlr::zstring_view m_svzOptionName_RemoveService = "remove-service";
	static constexpr vlr::zstring_view m_svzOptionDescription_RemoveService =
		"remove the component as a Windows service";

	static constexpr vlr::zstring_view m_svzOptionName_ServiceName = "service-name";
	static constexpr vlr::zstring_view m_svzOptionDescription_ServiceName =
		"the short (internal) name for the Windows service";

	static constexpr vlr::zstring_view m_svzOptionName_ServiceDescription = "service-description";
	static constexpr vlr::zstring_view m_svzOptionDescription_ServiceDescription =
		"the descriptive name for the Windows service";

};
