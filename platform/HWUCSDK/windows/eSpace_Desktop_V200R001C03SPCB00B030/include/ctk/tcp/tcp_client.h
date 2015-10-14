/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_TCP_CLIENT_H_
#define _Z_CTK_TCP_CLIENT_H_

#include "ctk/tcp/tcp_common.h"

namespace ctk {

    namespace tcp { class ClientImpl; }

    class CTK_API TcpClient
    {
        tcp::ClientImpl* impl_;

    public:
        TcpClient();
        ~TcpClient();

        bool open(const TcpAddr& _remote, TcpCallback* _cb);

        void close();

        bool send(ctk::rcistr _buf);

        ctk::uint16 getLocalPort() const;

    };

} // end of namespace ctk

#endif //_Z_CTK_TCP_CLIENT_H_

