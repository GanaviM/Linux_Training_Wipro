#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x1c0dd58c, "kobject_put" },
	{ 0x3854774b, "kstrtoll" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x8a409b4f, "sysfs_remove_group" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xdffb829d, "kobject_create_and_add" },
	{ 0xe95814c0, "sysfs_create_group" },
	{ 0x122c3a7e, "_printk" },
	{ 0x6ab589bc, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "728952C47F03ED7E6F7EC48");
