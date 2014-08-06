// The MIT License (MIT)

// Copyright (c) 2012-2014 Danny Y., Rapptz

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef GEARS_SYSTEM_WINDOWS_PROCESS_HPP
#define GEARS_SYSTEM_WINDOWS_PROCESS_HPP

#include "handle.hpp"
#if WINVER >= 0x602 // Windows 8 and higher
#include <Processthreadsapi.h>
#endif

namespace gears {
namespace system {
struct process {
    using id_type = DWORD;
private:
    id_type pid;
public:
    static constexpr id_type invalid_id = static_cast<id_type>(-1);

    id_type id() const noexcept {
        return pid;
    }

    id_type parent_id() const noexcept {
        handle snapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
        if(snapshot.get() == INVALID_HANDLE_VALUE) {
            return invalid_id;
        }

        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(pe);
        bool has_record = Process32First(snapshot.get(), &pe);
        while(has_record) {
            if(id == pe.th32ProcessID) {
                return pe.th32ParentProcessID;
            }
            has_record = Process32Next(snapshot.get(), &pe);
        }

        return invalid_id;
    }
};
} // system
} // gears

#endif // GEARS_SYSTEM_WINDOWS_PROCESS_HPP
