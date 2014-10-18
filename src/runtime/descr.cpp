// Copyright (c) 2014 Dropbox, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "codegen/compvars.h"
#include "runtime/types.h"

namespace pyston {

static Box* memberGet(BoxedMemberDescriptor* self, Box* inst, Box* owner) {
    RELEASE_ASSERT(self->cls == member_cls, "");

    Py_FatalError("unimplemented");
}

static Box* propertyNew(Box* cls, Box* fget, Box* fset, Box** args) {
    RELEASE_ASSERT(cls == property_cls, "");
    Box* fdel = args[0];
    Box* doc = args[1];

    return new BoxedProperty(fget, fset, fdel, doc);
}

void setupDescr() {
    member_cls->giveAttr("__name__", boxStrConstant("member"));
    member_cls->giveAttr("__get__", new BoxedFunction(boxRTFunction((void*)memberGet, UNKNOWN, 3)));
    member_cls->freeze();

    property_cls->giveAttr("__name__", boxStrConstant("property"));
    property_cls->giveAttr("__new__", new BoxedFunction(boxRTFunction((void*)propertyNew, UNKNOWN, 5, 4, false, false),
                                                        { None, None, None, None }));
    property_cls->freeze();
}

void teardownDescr() {
}
}
