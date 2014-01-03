/* Copyright (c) 2013-2014 Anton Titov.
 * Copyright (c) 2013-2014 pCloud Ltd.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of pCloud Ltd nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL pCloud Ltd BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ptasks.h"
#include "plibs.h"
#include "pdownload.h"

static void create_task(const char *path, uint64_t entryid, psync_syncid_t syncid, uint32_t type){
  psync_sql_res *res;
  res=psync_sql_prep_statement("INSERT INTO task (type, syncid, itemid, localpath) VALUES (?, ?, ?, ?)");
  psync_sql_bind_uint(res, 1, type);
  psync_sql_bind_uint(res, 2, syncid);
  psync_sql_bind_uint(res, 3, entryid);
  psync_sql_bind_string(res, 4, path);
  psync_sql_run(res);
  psync_sql_free_result(res);
  psync_wake_download();
}

void psync_task_create_local_folder(const char *path, psync_folderid_t folderid, psync_syncid_t syncid){
  create_task(path, folderid, syncid, PSYNC_CREATE_LOCAL_FOLDER);
}

void psync_task_delete_local_folder(const char *path, psync_folderid_t folderid, psync_syncid_t syncid){
  create_task(path, folderid, syncid, PSYNC_DELETE_LOCAL_FOLDER);
}

void psync_task_download_file(const char *path, psync_fileid_t fileid, psync_syncid_t syncid){
  create_task(path, fileid, syncid, PSYNC_DOWNLOAD_FILE);
}
