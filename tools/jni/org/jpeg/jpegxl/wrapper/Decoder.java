// Copyright (c) the JPEG XL Project Authors. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package org.jpeg.jpegxl.wrapper;

import java.nio.Buffer;
import java.nio.ByteBuffer;

/** JPEG XL JNI decoder wrapper. */
public class Decoder {
  /** Utility library, disable object construction. */
  private Decoder() {}

  /** One-shot decoding. */
  public static ImageData decode(Buffer data) {
    DecoderJni.BasicInfo basicInfo = DecoderJni.getBasicInfo(data);
    if (basicInfo.width < 0 || basicInfo.height < 0 || basicInfo.pixelsSize < 0
        || basicInfo.iccSize < 0) {
      throw new IllegalStateException("JNI has returned negative size");
    }
    Buffer pixels = ByteBuffer.allocateDirect(basicInfo.pixelsSize);
    Buffer icc = ByteBuffer.allocateDirect(basicInfo.iccSize);
    DecoderJni.getPixels(data, pixels, icc);
    return new ImageData(basicInfo.width, basicInfo.height, pixels, icc);
  }
}
