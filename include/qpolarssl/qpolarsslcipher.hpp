/** @file qpolarsslcipher.hpp
  * Qt wrapper class around polarssl functions
  *
  * @copyright (C) 2015, azadkuh
  * @date 2015.02.08
  * @version 1.0.0
  * @author amir zamani <azadkuh@live.com>
  *
 */

#ifndef QPOLARSSL_CIPHER_HPP
#define QPOLARSSL_CIPHER_HPP

#include "qpolarsslbase.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace qpolarssl {
///////////////////////////////////////////////////////////////////////////////
/** a wrapper class on polarssl cipher functions.
 * by this class, performing encryption/decryption by polarssl
 *  would be quite as simple as:
 * @code
    // psuedo code (no error checking for simplicity)
    QByteArray key(16, 'b');
    QByteArray nonce(16, 'k');
    qpolarssl::Cipher cipher("AES-128-CBC");

    cipher.setEncryptionKey(key);
    cipher.setIv(nonce);
    QByteArray encData = cipher("abcdefghijklmnopqrs");

    cipher.reset();
    cipher.setDecryptionKey(key);
    cipher.setIv(nonce);
    QByteArray plainData = cipher(encData);

    // now plainData is exactly equal to: abcdefghijklmnopqrs
 * @endcode
 */
class QPOLARSSL_API Cipher
{
public:
    /// checks if the specified cipher is supported.
    static bool     supports(TCipher type);

    /// checks if the specified (by name) cipher is supported.
    static bool     supports(const char* name);

public:
    /// constructs a Cipher instance by a cipher type.
    explicit        Cipher(TCipher t);

    /// constructs a Cipher instance by its name as "AES-128-CBC"
    explicit        Cipher(const char* name);

    virtual        ~Cipher();

    /** resets and clean internal states.
     * call after each encryption/decryption to make this instance reusable.
     */
    bool            reset();

    /// returns if this Cipher instace is valid or not.
    bool            isValid()const;

    /** does the encryption/decryption by Cipher instance in one function call.
     * @param message input message, could be in any length.
     * @param padding padding standard
     * @return the encrypted/decrypted result or an empty buffer as an error.
     */
    auto            operator()(const QByteArray& message,
                               TPadding padding = TPadding::PKCS7) -> QByteArray;
public:
    /// set the Cipher key for encryption.
    int             setEncryptionKey(const QByteArray& key);

    /// set the Cipher key for decryption.
    int             setDecryptionKey(const QByteArray& key);

    /// set the IV (aka nonce) of the Cipher message.
    int             setIv(const QByteArray& nonce);

protected:
    Q_DISABLE_COPY(Cipher)
    QScopedPointer<priv::Cipher>    d_ptr;
};

///////////////////////////////////////////////////////////////////////////////
} // namespace qpolarssl
///////////////////////////////////////////////////////////////////////////////
#endif // QPOLARSSL_CIPHER_HPP