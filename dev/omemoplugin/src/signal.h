/*
 * OMEMO Plugin for Psi
 * Copyright (C) 2018 Vyacheslav Karpukhin
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef PSIOMEMO_SIGNAL_H
#define PSIOMEMO_SIGNAL_H

#include <QObject>
#include <utility>
#include <qca_core.h>
#include "storage.h"

namespace psiomemo {
  class Bundle {
  public:
    Bundle() : signedPreKeyId(), signedPreKeyPublic(), signedPreKeySignature(), identityKeyPublic(), preKeys(), loaded(false) {
    };
    uint32_t signedPreKeyId;
    QByteArray signedPreKeyPublic;
    QByteArray signedPreKeySignature;
    QByteArray identityKeyPublic;
    QVector<QPair<uint32_t, QByteArray>> preKeys;
    bool loaded;
  };

  class EncryptedKey {
  public:
    EncryptedKey(uint32_t deviceId, bool isPreKey, QByteArray key)
        : deviceId(deviceId), isPreKey(isPreKey), key(qMove(key)) {}
    uint32_t deviceId;
    bool isPreKey;
    QByteArray key;
  };

  class Signal {
  public:
    void init(const QString &string);
    void deinit();
    Bundle collectBundle();
    void processBundle(const QString &from, uint32_t deviceId, const Bundle &bundle);
    uint32_t getDeviceId();
    void updateDeviceList(const QString &user, const QSet<uint32_t> &actualIds);
    QList<EncryptedKey> encryptKey(const QString &ownJid, const QString &recipient, const QCA::SymmetricKey &key);
    QPair<QByteArray, bool> decryptKey(const QString &sender, const EncryptedKey &encryptedKey);
    QVector<uint32_t> invalidSessions(const QString &recipient);
    uint32_t preKeyCount();
    bool isTrusted(const QString &user, uint32_t deviceId);
    void processUndecidedDevices(const QString &user, bool ownJid);
    bool isDisabledForUser(const QString &user);
    void setDisabledForUser(const QString &user, bool disabled);

  private:
    signal_context *m_signalContext = nullptr;
    uint32_t m_deviceId = 0;
    Storage m_storage;
    QByteArray getPublicKey(const ec_key_pair *key_pair) const;

    template<typename T>
    void doWithCipher(signal_protocol_address *addr, const QCA::SymmetricKey &key, T&&);
    signal_protocol_address getAddress(uint32_t deviceId, const QByteArray &name) const;
    bool sessionIsValid(const signal_protocol_address &addr) const;
    static void signal_log(int __unused level, const char *message, size_t len, void *user_data);
    ec_public_key* curveDecodePoint(const QByteArray &bytes) const;
    void generatePreKeys();
  };
}
#endif //PSIOMEMO_SIGNAL_H
