/*
 * Strawberry Music Player
 * This file was part of Clementine.
 * Copyright 2010, David Sansome <me@davidsansome.com>
 * Copyright 2018-2019, Jonas Kvinge <jonas@jkvinge.net>
 *
 * Strawberry is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Strawberry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Strawberry.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef NETWORK_H
#define NETWORK_H

#include "config.h"

#include <QtGlobal>
#include <QObject>
#include <QNetworkAccessManager>
#include <QAbstractNetworkCache>
#include <QMutex>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkCacheMetaData>

class QIODevice;
class QNetworkReply;
class QNetworkDiskCache;

class NetworkAccessManager : public QNetworkAccessManager {
  Q_OBJECT

 public:
  explicit NetworkAccessManager(QObject *parent = nullptr);

 protected:
  QNetworkReply *createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData) override;
};

class ThreadSafeNetworkDiskCache : public QAbstractNetworkCache {
 public:
  explicit ThreadSafeNetworkDiskCache(QObject *parent);
  ~ThreadSafeNetworkDiskCache() override;

  qint64 cacheSize() const override;
  QIODevice *data(const QUrl &url) override;
  void insert(QIODevice *device) override;
  QNetworkCacheMetaData metaData(const QUrl &url) override;
  QIODevice *prepare(const QNetworkCacheMetaData &metaData) override;
  bool remove(const QUrl &url) override;
  void updateMetaData(const QNetworkCacheMetaData &metaData) override;

  void clear() override;

 private:
  static QMutex sMutex;
  static ThreadSafeNetworkDiskCache *sInstance;
  static QNetworkDiskCache *sCache;
};

#endif  // NETWORK_H
