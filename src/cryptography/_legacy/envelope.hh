#if defined(INFINIT_CRYPTOGRAPHY_LEGACY)
# ifndef INFINIT_CRYPTOGRAPHY_LEGACY_ENVELOPE_HH
#  define INFINIT_CRYPTOGRAPHY_LEGACY_ENVELOPE_HH

#  include <cryptography/fwd.hh>
#  include <cryptography/Cipher.hh>
#  include <cryptography/Oneway.hh>

#  include <elle/types.hh>
#  include <elle/fwd.hh>

#  include <openssl/evp.h>

#  include <memory>

//
// ---------- Asymmetric ------------------------------------------------------
//

namespace infinit
{
  namespace cryptography
  {
    /// Contains high-level cryptographic operation known as envelope
    /// sealing/opening which concretely are encryption/decryption processes
    /// to handle larger amount of data than the asymmetric keys support.
    namespace envelope
    {
      /*----------.
      | Functions |
      `----------*/

      /// Seal the given plain with the provided encryption context and
      /// function.
      ///
      /// Note that a padding size is provided, in bits, representing the
      /// number of bits taken by the padding in the output code.
      elle::Buffer
      seal(elle::ConstWeakBuffer const& plain,
           ::EVP_PKEY_CTX* context,
           int (*function)(EVP_PKEY_CTX*,
                           unsigned char*,
                           size_t*,
                           const unsigned char*,
                           size_t),
           ::EVP_CIPHER const* cipher,
           ::EVP_MD const* oneway,
           uint32_t const padding_size);
      /// Open the envelope with the provided context and function.
      elle::Buffer
      open(elle::ConstWeakBuffer const& code,
           ::EVP_PKEY_CTX* context,
           int (*function)(EVP_PKEY_CTX*,
                           unsigned char*,
                           size_t*,
                           const unsigned char*,
                           size_t));
    }
  }
}

# endif
#else
# warning "LEGACY: this file should not have been included"
#endif
