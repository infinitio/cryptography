#ifndef INFINIT_CRYPTOGRAPHY_HASH_HH
# define INFINIT_CRYPTOGRAPHY_HASH_HH

# include <cryptography/fwd.hh>
# include <cryptography/Oneway.hh>
# include <cryptography/Digest.hh>

# include <elle/types.hh>

# include <openssl/evp.h>

# include <iosfwd>

namespace infinit
{
  namespace cryptography
  {
    /*----------.
    | Functions |
    `----------*/
# if !defined(INFINIT_CRYPTOGRAPHY_LEGACY)
    /// Hash a plain text and return a digest message.
    Digest
    hash(Plain const& plain,
         Oneway const oneway);
# endif

# if defined(INFINIT_CRYPTOGRAPHY_LEGACY)
    /*-------.
    | Legacy |
    `-------*/

    template <typename T = Plain>
    Digest
    hash(T const& value,
         Oneway oneway);
# endif
  }
}

# include <cryptography/hash.hxx>

#endif
