/***************************************************************************
    copyright            : (C) 2008 by Scott Wheeler
    email                : wheeler@kde.org
***************************************************************************/

/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#ifndef TAGLIB_WAVPROPERTIES_H
#define TAGLIB_WAVPROPERTIES_H

#include "taglib.h"
#include "audioproperties.h"

namespace Strawberry_TagLib {
namespace TagLib {

class ByteVector;

namespace RIFF {
namespace WAV {

class File;

//! An implementation of audio property reading for WAV

/*!
 * This reads the data from an WAV stream found in the AudioProperties
 * API.
 */

class TAGLIB_EXPORT AudioProperties : public Strawberry_TagLib::TagLib::AudioProperties {
 public:
  /*!
   * Create an instance of WAV::AudioProperties with the data read from the WAV::File \a file.
   */
  explicit AudioProperties(File *file, ReadStyle style);

  /*!
   * Destroys this WAV::AudioProperties instance.
   */
  virtual ~AudioProperties();

  /*!
   * Returns the length of the file in seconds.
   * The length is rounded down to the nearest whole second.
   *
   * \see lengthInMilliseconds()
   */
  virtual int lengthInSeconds() const;

  /*!
   * Returns the length of the file in milliseconds.
   *
   * \see lengthInSeconds()
   */
  virtual int lengthInMilliseconds() const;

  /*!
   * Returns the average bit rate of the file in kb/s.
   */
  virtual int bitrate() const;

  /*!
   * Returns the sample rate in Hz.
   */
  virtual int sampleRate() const;

  /*!
   * Returns the number of audio channels.
   */
  virtual int channels() const;

  /*!
   * Returns the number of bits per audio sample.
   */
  int bitsPerSample() const;

  /*!
   * Returns the number of sample frames.
   */
  unsigned int sampleFrames() const;

  /*!
   * Returns the format ID of the file.
   * 0 for unknown, 1 for PCM, 2 for ADPCM, 3 for 32/64-bit IEEE754, and so forth.
   *
   * \note For further information, refer to the WAVE Form Registration Numbers in RFC 2361.
   */
  int format() const;

 private:
  explicit AudioProperties(const AudioProperties&);
  AudioProperties &operator=(const AudioProperties&);

  void read(File *file);

  class AudioPropertiesPrivate;
  AudioPropertiesPrivate *d;
};

}  // namespace WAV
}  // namespace RIFF
}  // namespace TagLib
}  // namespace Strawberry_TagLib

#endif
