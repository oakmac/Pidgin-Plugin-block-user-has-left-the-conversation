/* MIT license */

#include "internal.h"
#include "debug.h"
#include "plugin.h"
#include "signals.h"
#include "version.h"

/** Plugin id : type-author-name (to guarantee uniqueness) */
#define SIMPLE_PLUGIN_ID "core-chrisoakman-blockuserhaslefttheconversation"

static gboolean
writing_im_msg_cb(PurpleAccount *account, const char *who, char **buffer,
				PurpleConversation *conv, PurpleMessageFlags flags, void *data)
{
	if (flags & PURPLE_MESSAGE_SYSTEM && strstr(*buffer, " has left the conversation.") != NULL) {
		purple_debug_misc("block <user> has left the conversation plugin", "blocked: <user> has left the conversation.\n");
		return TRUE;
	}
	else {
		return FALSE;
	}
}

static gboolean
plugin_load(PurplePlugin *plugin)
{
	void *conv_handle = purple_conversations_get_handle();
	
	purple_debug(PURPLE_DEBUG_INFO, "plugins", "block <user> has left the conversation plugin loaded.\n");

	purple_signal_connect(conv_handle, "writing-im-msg", plugin, PURPLE_CALLBACK(writing_im_msg_cb), NULL);	

	return TRUE;
}

static gboolean
plugin_unload(PurplePlugin *plugin)
{
	purple_debug(PURPLE_DEBUG_INFO, "plugins", "block <user> has left the conversation plugin unloaded.\n");

	return TRUE;
}

static PurplePluginInfo info =
{
	PURPLE_PLUGIN_MAGIC,
	PURPLE_MAJOR_VERSION,
	PURPLE_MINOR_VERSION,
	PURPLE_PLUGIN_STANDARD,                           /**< type           */
	NULL,                                             /**< ui_requirement */
	0,                                                /**< flags          */
	NULL,                                             /**< dependencies   */
	PURPLE_PRIORITY_DEFAULT,                          /**< priority       */

	SIMPLE_PLUGIN_ID,                                 /**< id             */
	N_("Block <user> has left the conversation."),                		  /**< name           */
	"1.0",                                  		/**< version        */
	                                                  /**  summary        */
	N_("Blocks system messages that tell you when someone has left the conversation."),
	                                                  /**  description    */
	N_("Blocks system messages that tell you when someone has left the conversation."),
	"Chris Oakman <chris@oakmac.com>",        /**< author         */
	"http://github.com/oakmac/Pidgin-Plugin-block-user-has-left-the-conversation/",                                     /**< homepage       */

	plugin_load,                                      /**< load           */
	plugin_unload,                                    /**< unload         */
	NULL,                                             /**< destroy        */

	NULL,                                             /**< ui_info        */
	NULL,                                             /**< extra_info     */
	NULL,
	NULL,
	/* Padding */
	NULL,
	NULL,
	NULL,
	NULL
};

static void
init_plugin(PurplePlugin *plugin)
{
}

PURPLE_INIT_PLUGIN(simple, init_plugin, info)