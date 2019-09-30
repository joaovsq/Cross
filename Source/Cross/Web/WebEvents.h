//
// Copyright (c) 2014-2016 THUNDERBEAST GAMES LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "../Core/Object.h"

namespace Cross
{

/// WebRequest has completed
CROSS_EVENT(E_WEBREQUESTCOMPLETE, WebRequestComplete)
{
    CROSS_PARAM(P_REQUEST, Request);    // WebRequest
    CROSS_PARAM(P_ERROR, Error);        // String
    CROSS_PARAM(P_DOWNLOAD, Download);  // Deserializer (BufferQueue)
    CROSS_PARAM(P_UPLOAD, Upload);      // Serializer (BufferQueue)
}

/// WebRequest progress event
CROSS_EVENT(E_WEBREQUESTPROGRESS, WebRequestProgress)
{
    CROSS_PARAM(P_REQUEST, Request);              // WebRequest
    CROSS_PARAM(P_DOWNLOADTOTAL, DownloadTotal);  // int
    CROSS_PARAM(P_DOWNLOADED, Downloaded);        // int
    CROSS_PARAM(P_UPLOADTOTAL, UploadTotal);      // int
    CROSS_PARAM(P_UPLOADED, Uploaded);            // int
}

CROSS_EVENT(E_WEBREQUESTDOWNLOADCHUNK, WebRequestDownloadChunk)
{
    CROSS_PARAM(P_REQUEST, Request);     // WebRequest
    CROSS_PARAM(P_DOWNLOAD, Download);   // Deserializer (BufferQueue)
    CROSS_PARAM(P_CHUNKSIZE, ChunkSize);  // unsigned
}

CROSS_EVENT(E_WEBREQUESTUPLOADCHUNK, WebRequestUploadChunk)
{
    CROSS_PARAM(P_REQUEST, Request);       // WebRequest
    CROSS_PARAM(P_UPLOAD, Upload);         // Serializer (BufferQueue)
    CROSS_PARAM(P_BYTESREMAINING, BytesRemaining);   // unsigned
}

}
