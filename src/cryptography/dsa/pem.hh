#ifndef INFINIT_CRYPTOGRAPHY_DSA_PEM_HH
# define INFINIT_CRYPTOGRAPHY_DSA_PEM_HH

# include <cryptography/dsa/PublicKey.hh>
# include <cryptography/dsa/PrivateKey.hh>
# include <cryptography/dsa/KeyPair.hh>
# include <cryptography/dsa/defaults.hh>
# include <cryptography/pem.hh>

# include <boost/filesystem.hpp>

namespace infinit
{
  namespace cryptography
  {
    namespace dsa
    {
      namespace pem
      {
        /*----------.
        | Functions |
        `----------*/

        /// Import an DSA public key from a path.
        PublicKey
        import_K(boost::filesystem::path const& path,
                 Oneway const digest_algorithm =
                   defaults::digest_algorithm);
        /// Import an DSA private key from a path.
        PrivateKey
        import_k(boost::filesystem::path const& path,
                 elle::String const& passphrase =
                   cryptography::pem::defaults::passphrase,
                 Oneway const digest_algorithm =
                   defaults::digest_algorithm);
        /// Import an DSA key pair from a path.
        KeyPair
        import_keypair(boost::filesystem::path const& path,
                       elle::String const& passphrase =
                         cryptography::pem::defaults::passphrase,
                       Oneway const digest_algorithm =
                         defaults::digest_algorithm);
        /// Export an DSA public key.
        void
        export_K(PublicKey const& K,
                 boost::filesystem::path const& path);
        /// Export an DSA private key, providing the passphrase, cipher and
        /// mode to encrypt it with.
        void
        export_k(PrivateKey const& k,
                 boost::filesystem::path const& path,
                 elle::String const& passphrase =
                   cryptography::pem::defaults::passphrase,
                 Cipher const& cipher =
                   cryptography::pem::defaults::cipher,
                 Mode const& mode =
                   cryptography::pem::defaults::mode);
        /// Export an DSA key pair.
        void
        export_keypair(KeyPair const& keypair,
                       boost::filesystem::path const& path,
                       elle::String const& passphrase =
                         cryptography::pem::defaults::passphrase,
                       Cipher const& cipher =
                         cryptography::pem::defaults::cipher,
                       Mode const& mode =
                         cryptography::pem::defaults::mode);
      }
    }
  }
}

#endif
