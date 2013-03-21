#ifndef INFINIT_CRYPTOGRAPHY_EVP_HH
# define INFINIT_CRYPTOGRAPHY_EVP_HH

# include <cryptography/fwd.hh>
# include <cryptography/Code.hh>

# include <openssl/evp.h>

//
// ---------- Asymmetric ------------------------------------------------------
//

namespace infinit
{
  namespace cryptography
  {
    namespace evp
    {
      /// Contain the operations related to asymmetric cryptosystems.
      namespace asymmetric
      {
        /*----------.
        | Functions |
        `----------*/

        /// Encrypt the given plain with the provided encryption context and
        /// function.
        Code
        encrypt(Plain const& plain,
                ::EVP_PKEY_CTX* context,
                int (*function)(EVP_PKEY_CTX*,
                                unsigned char*,
                                size_t*,
                                const unsigned char*,
                                size_t));
        /// Decrypt the code with the provided context and function.
        Clear
        decrypt(Code const& code,
                ::EVP_PKEY_CTX* context,
                int (*function)(EVP_PKEY_CTX*,
                                unsigned char*,
                                size_t*,
                                const unsigned char*,
                                size_t));
        /// Return true if the signature is valid according to the given plain.
        elle::Boolean
        verify(Signature const& signature,
               Plain const& plain,
               ::EVP_PKEY_CTX* context,
               int (*function)(EVP_PKEY_CTX*,
                               const unsigned char*,
                               size_t,
                               const unsigned char*,
                               size_t));
        /// Sign the given plain text.
        Signature
        sign(Plain const& plain,
             ::EVP_PKEY_CTX* context,
             int (*function)(EVP_PKEY_CTX*,
                             unsigned char*,
                             size_t*,
                             const unsigned char*,
                             size_t));
      }
    }
  }
}

//
// ---------- Symmetric -------------------------------------------------------
//

namespace infinit
{
  namespace cryptography
  {
    namespace evp
    {
      /// Contain the operations related to symmetric algorithms.
      namespace symmetric
      {
        /// Encrypt the plain text according to the given secret and functions.
        Code
        encrypt(Plain const& plain,
                elle::Buffer const& secret,
                ::EVP_CIPHER const* function_cipher,
                ::EVP_MD const* function_oneway);
        /// Decrypt the ciphered text according to the given secret and
        /// functions.
        Clear
        decrypt(Code const& code,
                elle::Buffer const& secret,
                ::EVP_CIPHER const* function_cipher,
                ::EVP_MD const* function_oneway);
      }
    }
  }
}

//
// ---------- Digest ----------------------------------------------------------
//

namespace infinit
{
  namespace cryptography
  {
    namespace evp
    {
      namespace digest
      {
        /// Hash the given plain text with the message digest function.
        Digest
        hash(Plain const& plain,
             ::EVP_MD const* function);
      }
    }
  }
}

#endif