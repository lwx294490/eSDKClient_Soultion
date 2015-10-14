/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Name Type Value

#ifndef _Z_PML_NTV_BYTES_VALUE_H_
#define _Z_PML_NTV_BYTES_VALUE_H_

#include "ctk/ctk_config.h"

#include "ctk/pml/ntv_valuebase.h"

namespace ctk {
namespace pml {
namespace ntv {

    class CTK_API BytesValue : public ValueBase
    {
    public:
        typedef BytesValue _Self;
        typedef ValueBase _Super;
        typedef Bytes store_type;
        typedef istr value_type;

    public:
        BytesValue(Unit* _owner=0);
        BytesValue(value_type _v, Unit* _owner=0);

        _Self& operator=(value_type _v);
        _Self& assign(value_type _v);

        const store_type& data() const;

        static _Self* create(value_type _v);

        virtual bool single() const;
        virtual _Self* clone() const;
        virtual std::ostream& dump(std::ostream& _os) const;
        virtual ctk::dumper& dump(ctk::dumper& _os) const;

    private:
        store_type data_;
    };

} // end of namespace ntv
} // end of namespace pml
} // end of namespace ctk

#endif // !_Z_PML_NTV_BYTES_VALUE_H_

