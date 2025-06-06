/*
 * Copyright (C) 2025 The pgmoneta community
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may
 * be used to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* pgmoneta */
#include <pgmoneta.h>
#include <utils.h>

/* system */
#ifdef DEBUG
#include <assert.h>
#endif
#include <stdlib.h>
#include <string.h>

static struct message* message = NULL;
static void* data = NULL;

void
pgmoneta_memory_init(void)
{
   if (message == NULL)
   {
      message = (struct message*)malloc(sizeof(struct message));

      if (message == NULL)
      {
         return;
      }

      data = aligned_alloc((size_t)ALIGNMENT_SIZE, DEFAULT_BUFFER_SIZE);

      if (data == NULL)
      {
         return;
      }
   }

   pgmoneta_memory_free();
}

struct message*
pgmoneta_memory_message(void)
{
#ifdef DEBUG
   assert(message != NULL);
   assert(data != NULL);
#endif

   return message;
}

void
pgmoneta_memory_free(void)
{
#ifdef DEBUG
   assert(message != NULL);
   assert(data != NULL);
#endif

   memset(message, 0, sizeof(struct message));
   memset(data, 0, DEFAULT_BUFFER_SIZE);

   message->kind = 0;
   message->length = 0;
   message->data = data;
}

void
pgmoneta_memory_destroy(void)
{
   free(data);
   free(message);

   data = NULL;
   message = NULL;
}

void*
pgmoneta_memory_dynamic_create(size_t* size)
{
   *size = 0;

   return NULL;
}

void
pgmoneta_memory_dynamic_destroy(void* data)
{
   free(data);
}

void*
pgmoneta_memory_dynamic_append(void* orig, size_t orig_size, void* append, size_t append_size, size_t* new_size)
{
   void* d = NULL;
   size_t s;

   if (append != NULL)
   {
      s = orig_size + append_size;
      d = realloc(orig, s);
      memcpy(d + orig_size, append, append_size);
   }
   else
   {
      s = orig_size;
      d = orig;
   }

   *new_size = s;

   return d;
}

void
pgmoneta_memory_stream_buffer_init(struct stream_buffer** buffer)
{
   struct stream_buffer* b = malloc(sizeof(struct stream_buffer));

   if (b == NULL)
   {
      *buffer = NULL;
      return;
   }

   b->size = DEFAULT_BUFFER_SIZE;
   b->start = b->end = b->cursor = 0;
   b->buffer = aligned_alloc((size_t)ALIGNMENT_SIZE, DEFAULT_BUFFER_SIZE);
   *buffer = b;
}

int
pgmoneta_memory_stream_buffer_enlarge(struct stream_buffer* buffer, int bytes_needed)
{
   size_t new_size = 0;
   void* new_buffer = NULL;

   if (buffer->size + bytes_needed < buffer->size + DEFAULT_BUFFER_SIZE)
   {
      new_size = pgmoneta_get_aligned_size(buffer->size + DEFAULT_BUFFER_SIZE);
   }
   else
   {
      new_size = pgmoneta_get_aligned_size(buffer->size + bytes_needed);
   }

   if (buffer->size > new_size)
   {
      return 0;
   }

   new_buffer = aligned_alloc((size_t)ALIGNMENT_SIZE, new_size);

   if (new_buffer == NULL)
   {
      return 1;
   }

   memset(new_buffer, 0, new_size);
   memcpy(new_buffer, buffer->buffer, buffer->size);

   free(buffer->buffer);

   buffer->size = new_size;
   buffer->buffer = new_buffer;

   return 0;
}

void
pgmoneta_memory_stream_buffer_free(struct stream_buffer* buffer)
{
   if (buffer == NULL)
   {
      return;
   }
   if (buffer->buffer != NULL)
   {
      free(buffer->buffer);
      buffer->buffer = NULL;
   }
   free(buffer);
}
