#pragma once

#include "configuration/UWGMClientIni.hpp"
#include "utilities/Logger.hpp"


#include <wwgmtkcustomizer.h>
#include <memory>

class UWGMNeutralDataAttachPluginCustomizer : public virtual wwgmtkClientCustomizer
{
public:
	UWGMNeutralDataAttachPluginCustomizer();
	~UWGMNeutralDataAttachPluginCustomizer();

	xint initialize(wwgmtkClient_ptr client);

	xanydictionary_ptr executeCommand(xanydictionary_ptr params);

	xstring executeJSCommand(xrstring params);

	void showMessage(xstring msg, xint msgType, xbool forceUWGMClientPrint = xtrue, xbool toFile = xtrue);

	wwgmtkClient_ptr getClient()
	{
		return m_Client;
	}

	UWGMClientIni* getClientIni()
	{
		return m_ClientIni;
	}

protected:
	wwgmtkClient_ptr m_Client;
	UWGMClientIni *m_ClientIni;
};

typedef xrchandle<UWGMNeutralDataAttachPluginCustomizer> UWGMNeutralDataAttachPluginCustomizer_ptr;
