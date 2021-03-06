/*
 *  Copyright (C) 2005  Anthony Liguori <anthony@codemonkey.ws>
 *
 *  Network Block Device Common Code
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; under version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "nbd-internal.h"

/* nbd_wr_syncv
 * The function may be called from coroutine or from non-coroutine context.
 * When called from non-coroutine context @ioc must be in blocking mode.
 */
ssize_t nbd_rwv(QIOChannel *ioc, struct iovec *iov, size_t niov, size_t length,
                bool do_read, Error **errp)
{
    ssize_t done = 0;
    struct iovec *local_iov = g_new(struct iovec, niov);
    struct iovec *local_iov_head = local_iov;
    unsigned int nlocal_iov = niov;

    nlocal_iov = iov_copy(local_iov, nlocal_iov, iov, niov, 0, length);

    while (nlocal_iov > 0) {
        ssize_t len;
        if (do_read) {
            len = qio_channel_readv(ioc, local_iov, nlocal_iov, errp);
        } else {
            len = qio_channel_writev(ioc, local_iov, nlocal_iov, errp);
        }
        if (len == QIO_CHANNEL_ERR_BLOCK) {
            /* errp should not be set */
            assert(qemu_in_coroutine());
            qio_channel_yield(ioc, do_read ? G_IO_IN : G_IO_OUT);
            continue;
        }
        if (len < 0) {
            done = -EIO;
            goto cleanup;
        }

        if (do_read && len == 0) {
            break;
        }

        iov_discard_front(&local_iov, &nlocal_iov, len);
        done += len;
    }

 cleanup:
    g_free(local_iov_head);
    return done;
}

/* Discard length bytes from channel.  Return -errno on failure and 0 on
 * success */
int nbd_drop(QIOChannel *ioc, size_t size, Error **errp)
{
    ssize_t ret = 0;
    char small[1024];
    char *buffer;

    buffer = sizeof(small) >= size ? small : g_malloc(MIN(65536, size));
    while (size > 0) {
        ssize_t count = MIN(65536, size);
        ret = nbd_read(ioc, buffer, MIN(65536, size), errp);

        if (ret < 0) {
            goto cleanup;
        }
        size -= count;
    }

 cleanup:
    if (buffer != small) {
        g_free(buffer);
    }
    return ret;
}


void nbd_tls_handshake(QIOTask *task,
                       void *opaque)
{
    struct NBDTLSHandshakeData *data = opaque;

    qio_task_propagate_error(task, &data->error);
    data->complete = true;
    g_main_loop_quit(data->loop);
}
