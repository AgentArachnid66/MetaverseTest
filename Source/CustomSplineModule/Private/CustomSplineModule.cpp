#include "CustomSplineModule.h"

#define LOCTEXT_NAMESPACE "FCustomSplineModuleModule"

void FCustomSplineModuleModule::StartupModule()
{
}

void FCustomSplineModuleModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FCustomSplineModuleModule, CustomSplineModule)

DEFINE_LOG_CATEGORY(LogCustomSplineModule);