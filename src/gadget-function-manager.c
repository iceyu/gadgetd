/*
 * gadget-function-manager.c
 * Copyright(c) 2012-2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0(the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <gio/gio.h>

#include <gadget-daemon.h>
#include "gadgetd-gdbus-codegen.h"
#include <gadget-function-manager.h>

typedef struct _GadgetFunctionManagerClass   GadgetFunctionManagerClass;

struct _GadgetFunctionManager
{
	GadgetdGadgetFunctionManagerSkeleton parent_instance;

	gchar *gadget_name;
};

struct _GadgetFunctionManagerClass
{
	GadgetdGadgetFunctionManagerSkeletonClass parent_class;
};

enum
{
	PROP_0,
	PROP_GADGET_NAME
} prop_func_manager;

/**
 * @brief gadget function manager iface init
 * @param[in] iface GadgetdGadgetFunctionManagerIface
 */
static void gadget_function_manager_iface_init(GadgetdGadgetFunctionManagerIface *iface);

/**
 * @brief G_DEFINE_TYPE_WITH_CODE
 * @details A convenience macro for type implementations. Similar to G_DEFINE_TYPE(), but allows
 * to insert custom code into the *_get_type() function,
 * @see G_DEFINE_TYPE()
 */
G_DEFINE_TYPE_WITH_CODE(GadgetFunctionManager, gadget_function_manager, GADGETD_TYPE_GADGET_FUNCTION_MANAGER_SKELETON,
			 G_IMPLEMENT_INTERFACE(GADGETD_TYPE_GADGET_FUNCTION_MANAGER, gadget_function_manager_iface_init));

/**
 * @brief gadget function manager init
 * @param[in] function_manager GadgetFunctionManager struct
 */
static void
gadget_function_manager_init(GadgetFunctionManager *function_manager)
{
	/* noop */
}

/**
 * @brief gadget function manager finalize
 * @param[in] object GObject
 */
static void
gadget_function_manager_finalize(GObject *object)
{
	GadgetFunctionManager *function_manager = GADGET_FUNCTION_MANAGER(object);

	g_free(function_manager->gadget_name);

	if (G_OBJECT_CLASS(gadget_function_manager_parent_class)->finalize != NULL)
		G_OBJECT_CLASS(gadget_function_manager_parent_class)->finalize(object);
}

/**
 * @brief gadget function manager Set property
 * @param[in] object a GObject
 * @param[in] property_id numeric id under which the property was registered with
 * @param[in] value a new GValue for the property
 * @param[in] pspec the GParamSpec structure describing the property
 */
static void
gadget_function_manager_set_property(GObject            *object,
				      guint               property_id,
				      const GValue       *value,
				      GParamSpec         *pspec)
{
	GadgetFunctionManager *fun_manager = GADGET_FUNCTION_MANAGER(object);

	switch(property_id) {
	case PROP_GADGET_NAME:
		g_assert(fun_manager->gadget_name == NULL);
		fun_manager->gadget_name = g_value_dup_string(value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
		break;
	}
}

/**
* @brief gadget function manager get property.
* @details generic Getter for all properties of this type
* @param[in] object a GObject
* @param[in] property_id numeric id under which the property was registered with
* @param[in] value a GValue to return the property value in
* @param[in] pspec the GParamSpec structure describing the property
*/
static void
gadget_function_manager_get_property(GObject          *object,
                                    guint             property_id,
                                    GValue           *value,
                                    GParamSpec       *pspec)
{
	switch(property_id) {
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
		break;
	}
}

/**
 * @brief gadget function manager class init
 * @param[in] klass GadgetFunctionManagerClass
 */
static void
gadget_function_manager_class_init(GadgetFunctionManagerClass *klass)
{
	GObjectClass *gobject_class;

	gobject_class = G_OBJECT_CLASS(klass);
	gobject_class->finalize     = gadget_function_manager_finalize;
	gobject_class->set_property = gadget_function_manager_set_property;
	gobject_class->get_property = gadget_function_manager_get_property;

	g_object_class_install_property(gobject_class,
                                   PROP_GADGET_NAME,
                                   g_param_spec_string("gadget_name",
                                                       "Gadget name",
                                                       "gadget name",
                                                       NULL,
                                                       G_PARAM_READABLE |
                                                       G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
}

/**
 * @brief gadget function manager new
 * @details Create a new GadgetFunctionManager instance
 * @param[in] daemon GadgetDaemon
 * @return GadgetFunctionManager object neet to be free.
 */
GadgetFunctionManager *
gadget_function_manager_new(const gchar *gadget_name)
{
	g_return_val_if_fail(gadget_name != NULL, NULL);

	GadgetFunctionManager *object;

	object = g_object_new(GADGET_TYPE_FUNCTION_MANAGER,
			       "gadget_name", gadget_name,
			        NULL);

	return object;
}

/**
 * @brief Create function handler
 * @param[in] object
 * @param[in] invocation
 * @param[in] instance
 * @param[in] type
 * @return true if metod handled
 */
static gboolean
handle_create_function(GadgetdGadgetFunctionManager	*object,
		        GDBusMethodInvocation		*invocation,
		        const gchar			*instance,
		        const gchar			*_type)
{
	/* TODO add create function handler */
	INFO("handled create function");

	return TRUE;
}

/**
 * @brief remove function handler
 * @param[in] object
 * @param[in] invocation
 * @param[in] function_path
 * @return true if metod handled
 */
static gboolean
handle_remove_function(GadgetdGadgetFunctionManager	*object,
			GDBusMethodInvocation		*invocation,
			const gchar			*function_path)
{
	/* TODO add remove function handler */
	INFO("remove function handler");

	return TRUE;
}

/**
 * @brief find function by name handler
 * @param[in] object
 * @param[in] invocation
 * @param[in] function_name
 * @return true if metod handled
 */
static gboolean
handle_find_function_by_name(GadgetdGadgetFunctionManager	*object,
		      GDBusMethodInvocation			*invocation,
		      const gchar				*function_name)
{
	/* TODO add find function by name handler*/
	INFO("find function by name handler");

	return TRUE;
}

/**
 * @brief gadget function manager iface init
 * @param[in] iface GadgetdGadgetFunctionManagerIface
 */
static void
gadget_function_manager_iface_init(GadgetdGadgetFunctionManagerIface *iface)
{
	iface->handle_create_function = handle_create_function;
	iface->handle_remove_function = handle_remove_function;
	iface->handle_find_function_by_name = handle_find_function_by_name;
}

