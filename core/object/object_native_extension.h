/*************************************************************************/
/*  object_native_extension.h                                                             */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef OBJECT_NATIVE_EXTENSION_H
#define OBJECT_NATIVE_EXTENSION_H

#include "core/extension/gdnative_interface.h"
#include "core/string_name.h"

struct ObjectNativeExtension {
	// FIXME what would need to be done: split the C++ fields (StringName, bool) into separate struct which is accessible in object.h
	// then
	ObjectNativeExtension *parent = nullptr;
	List<ObjectNativeExtension *> children;
	StringName parent_class_name;
	StringName class_name;
	bool editor_class = false;
	GDNativeExtensionClassSet set;
	GDNativeExtensionClassGet get;
	GDNativeExtensionClassGetPropertyList get_property_list;
	GDNativeExtensionClassFreePropertyList free_property_list;
	GDNativeExtensionClassPropertyCanRevert property_can_revert;
	GDNativeExtensionClassPropertyGetRevert property_get_revert;
	GDNativeExtensionClassNotification notification;
	GDNativeExtensionClassToString to_string;
	GDNativeExtensionClassReference reference;
	GDNativeExtensionClassReference unreference;
	GDNativeExtensionClassGetRID get_rid;

	_FORCE_INLINE_ bool is_class(const String &p_class) const {
		const ObjectNativeExtension *e = this;
		while (e) {
			if (p_class == e->class_name.operator String()) {
				return true;
			}
			e = e->parent;
		}
		return false;
	}
	void *class_userdata = nullptr;

	GDNativeExtensionClassCreateInstance create_instance;
	GDNativeExtensionClassFreeInstance free_instance;
	GDNativeExtensionClassGetVirtual get_virtual;
};

#endif // OBJECT_NATIVE_EXTENSION_H
