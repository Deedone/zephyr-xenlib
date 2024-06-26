/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright (c) 2023 EPAM Systems
 *
 */

#pragma once
#include <zephyr/xen/public/xen.h>

#ifdef __cplusplus
extern "C" {
#endif

enum xs_perm {
	XS_PERM_NONE = 0x0,
	XS_PERM_READ = 0x1,
	XS_PERM_WRITE = 0x2,
	XS_PERM_BOTH = XS_PERM_WRITE | XS_PERM_READ
};

/*
 * Read the value associated with a path.
 *
 * @param path Xenstore path
 * @param value pre-allocated buffer for Xenstore value
 * @param len size of pre-allocated buffer
 * @return 0 on success, a negative errno value on error.
 */
int xss_read(const char *path, char *value, size_t len);

/*
 * Associates a value with a path.
 *
 * @param path Xenstore path
 * @param value Xenstore value
 * @return 0 on success, a negative errno value on error.
 */
int xss_write(const char *path, const char *value);

/*
 * Associates a value with a path and set read-write permissions for given domid.
 *
 * @param path Xenstore path
 * @param value Xenstore value
 * @return 0 on success, a negative errno value on error.
 */
int xss_write_guest_domain_rw(const char *path, const char *value, uint32_t domid);

/*
 * Associates a value with a path and set read-only permissions for given domid.
 *
 * @param path Xenstore path
 * @param value Xenstore value
 * @return 0 on success, a negative errno value on error.
 */
int xss_write_guest_domain_ro(const char *path, const char *value, uint32_t domid);

/*
 * Associates a value with a path and set none for domid1 and read-only for domid2
 * permissions.
 *
 * @param path Xenstore path
 * @param value Xenstore value
 * @param domid1 domain id with XS_PERM_NONE
 * @param domid2 domain id with XS_PERM_READ
 * @return 0 on success, a negative errno value on error.
 */
int xss_write_guest_with_permissions(const char *path, const char *value, uint32_t domid1,
				     uint32_t domid2);

/*
 * Read path and parse it as an integer.
 *
 * @param path Xenstore path
 * @param value Returned int value
 * @return 0 on success, a negative errno value on error.
 */
int xss_read_integer(const char *path, int *value);

/*
 * Sets permissions for input path and domid.
 *
 * @param path Xenstore path
 * @param domid Domain ID
 * @param perm Permission value
 * @return 0 on success, a negative errno value on error.
 */
int xss_set_perm(const char *path, domid_t domid, enum xs_perm perm);

/*
 * Removes the value associated with a path.
 *
 * @param path Xenstore path
 * @return 0 on success, a negative errno value on error.
 */
int xss_rm(const char *path);

/*
 * List all entries in a directory.
 *
 * @param path Xenstore path
 * @param len Number of entries in the directory
 * @return Dynamically allocated array of dynamically allocated strings with directory entries
 */
char **xss_list_entries(const char *path, int *len);

#ifdef __cplusplus
}
#endif
