// vlr-update.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "vlr-util/UtilMacros.Assertions.h"
#include "vlr-util/win32.ServiceControl.h"

#include "ComponentConfigOptionsManager.h"

HRESULT TestServiceCreate()
{
    TCHAR szPath[MAX_PATH];
    ::GetModuleFileName( NULL, szPath, MAX_PATH );

    auto oServiceConfig = vlr::win32::CServiceConfig{}
        .With_ServiceName( _T( "MyService" ) )
        .With_ServiceName_Display( _T( "Test Service" ) )
        .With_FilePath_ServiceBinary( szPath )
        ;

    HRESULT hr;

    auto oServiceControl = vlr::win32::CServiceControl{};
    hr = oServiceControl.Connect( vlr::ops::CNetworkTargetInfo::ForLocalSystem() );
    ASSERT_HR_SUCCEEDED__OR_RETURN_HRESULT( hr );

    SC_HANDLE hService{};
    hr = oServiceControl.SCM_CreateService(
        oServiceConfig,
        hService );
    ASSERT_HR_SUCCEEDED__OR_RETURN_HRESULT( hr );
    auto oOnDestroy_CloseService = vlr::util::CAutoCleanup_SC_HANDLE{ hService };

    hr = oServiceControl.SCM_DeleteService(
        hService );
    ASSERT_HR_SUCCEEDED__OR_RETURN_HRESULT( hr );

    return S_OK;
}

int main()
{
    std::cout << "Hello World!\n";

    //TestServiceCreate();

    auto oComponentConfigOptionsManager = CComponentConfigOptionsManager{};
    auto oConfigOptions = oComponentConfigOptionsManager.GetPopulatedOptions();

    std::cout << "Install service? " << oConfigOptions.m_obInstallService.value_or( false ) << std::endl;
}
