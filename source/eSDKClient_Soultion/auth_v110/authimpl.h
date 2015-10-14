#ifndef __AUTH_IMPL_H_
#define __AUTH_IMPL_H_

#include <string>
#include <comutil.h>
#include "auth/auth.h"
#include "COM_eSDKSSO_i.h"
#include "COM_eSDKSSO_i.c"


namespace uc {
    namespace model {
        namespace auth {

            class AuthManagerImpl : public AuthManager
            {
            public:
                virtual AuthType GetTicket(std::string &_ticket);
                virtual bool GetServer(std::string &_ipAddress, std::string &_port);
			public:
				bool init();
				void uninit();
				bool CheckIpAndPort(const char *ip, const char *port);
			private:
				IComIdl_eSDKSSO *m_pIntf;
			public:
				static AuthManagerImpl* m_pInstance;
            };

        } // namespace auth
    } // namespace model
} // namespace uc

#endif
