#include "pch.hpp"

#include "customizer/UWGMNeutralDataAttachPluginCustomizer.hpp"

#include <wwgmtk.h>


wwgmtkClientCustomizer_ptr wwgmtkGetCustomizer()
{
    return new UWGMNeutralDataAttachPluginCustomizer();
}
