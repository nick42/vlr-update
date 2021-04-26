#include "pch.h"
#include "ComponentConfigOptionsManager.h"

HRESULT CComponentConfigOptionsManager::PopulateConfigOptions()
{
	HRESULT hr;

	hr = PopulateConfigOptionsMapping();
	ASSERT_HR_SUCCEEDED__OR_RETURN_HRESULT( hr );

	hr = PopulateConfigOptions_ViaCommandLine_Implicit();
	ASSERT_HR_SUCCEEDED__OR_RETURN_HRESULT( hr );

	return S_OK;
}

HRESULT CComponentConfigOptionsManager::PopulateConfigOptionsMapping()
{
	auto& oConfigOptionsAndPopulationInfo = GetSharedComponentOptions();
	auto& oConfigOptions = oConfigOptionsAndPopulationInfo.m_oComponentConfigOptions;

	oConfigOptions.AddOptionMapping_Basic_Flag( m_svzOptionName_InstallService, oConfigOptions.m_obInstallService );
	oConfigOptions.AddOptionMapping_Basic_Flag( m_svzOptionName_RemoveService, oConfigOptions.m_obRemoveService );
	oConfigOptions.AddOptionMapping_Basic_StringValue( m_svzOptionName_ServiceName, oConfigOptions.m_osServiceName );

	return S_OK;
}

HRESULT CComponentConfigOptionsManager::PopulateConfigOptions_ViaCommandLine( const vlr::ModuleContext::Runtime::CCommandLine& oCommandLine )
{
	HRESULT hr;

	auto& oConfigOptionsAndPopulationInfo = GetSharedComponentOptions();
	auto& oConfigOptions = oConfigOptionsAndPopulationInfo.m_oComponentConfigOptions;

	hr = oConfigOptions.ParseOptions_CommandLine_withBoost( oCommandLine, &GetOptionsDesc_All );
	ASSERT_HR_SUCCEEDED__OR_RETURN_HRESULT( hr );

	return S_OK;
}

HRESULT CComponentConfigOptionsManager::PopulateConfigOptions_ViaCommandLine_Implicit()
{
	HRESULT hr;

	auto oCommandLine = vlr::ModuleContext::Runtime::CCommandLine{};
	hr = oCommandLine.SetFromOS_Implicit();
	ASSERT_HR_SUCCEEDED__OR_RETURN_HRESULT( hr );

	hr = PopulateConfigOptions_ViaCommandLine( oCommandLine );
	ASSERT_HR_SUCCEEDED__OR_RETURN_HRESULT( hr );

	return S_OK;
}

const CComponentConfigOptions& CComponentConfigOptionsManager::GetPopulatedOptions()
{
	auto& oConfigOptionsAndPopulationInfo = GetSharedComponentOptions();
	if (oConfigOptionsAndPopulationInfo.IsPopulated())
	{
		return oConfigOptionsAndPopulationInfo.m_oComponentConfigOptions;
	}

	PopulateConfigOptions();

	return oConfigOptionsAndPopulationInfo.m_oComponentConfigOptions;
}

CComponentConfigOptionsManager::CConfigOptionsAndPopulationInfo& CComponentConfigOptionsManager::GetSharedComponentOptions()
{
	static CConfigOptionsAndPopulationInfo oConfigOptionsAndPopulationInfo;
	return oConfigOptionsAndPopulationInfo;
}

const boost::program_options::options_description& CComponentConfigOptionsManager::GetOptionsDesc_All()
{
	static const auto oOptionsDesc_All = []
	{
		static boost::program_options::options_description oOptionsDesc( "Available options" );

		oOptionsDesc.add_options()
			(m_svzOptionName_Help, m_svzOptionDescription_Help)
			(m_svzOptionName_InstallService, boost::program_options::value<bool>(), m_svzOptionDescription_InstallService)
			(m_svzOptionName_RemoveService, boost::program_options::value<bool>(), m_svzOptionDescription_RemoveService)
			(m_svzOptionName_ServiceName, boost::program_options::value<std::string>(), m_svzOptionDescription_ServiceName)
			(m_svzOptionName_ServiceDescription, boost::program_options::value<std::string>(), m_svzOptionDescription_ServiceDescription)
			;

		return oOptionsDesc;
	}();

	return oOptionsDesc_All;
}
