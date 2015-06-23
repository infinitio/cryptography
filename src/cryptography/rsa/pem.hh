#ifndef INFINIT_CRYPTOGRAPHY_RSA_PEM_HH
# define INFINIT_CRYPTOGRAPHY_RSA_PEM_HH

# include <cryptography/rsa/Padding.hh>
# include <cryptography/rsa/KeyPair.hh>
# include <cryptography/rsa/defaults.hh>
# include <cryptography/pem.hh>

# include <boost/filesystem.hpp>

namespace infinit
{
  namespace cryptography
  {
    namespace rsa
    {
      namespace pem
      {
        /*----------.
        | Functions |
        `----------*/

        /// Import an RSA public key from a path.
        PublicKey
        import_K(boost::filesystem::path const& path,
                 Padding const encryption_padding =
                   defaults::encryption_padding,
                 Padding const signature_padding =
                   defaults::signature_padding,
                 Oneway const digest_algorithm =
                   defaults::digest_algorithm,
                 Cipher const envelope_cipher =
                   defaults::envelope_cipher,
                 Mode const envelope_mode =
                   defaults::envelope_mode);
        /// Import an RSA private key from a path.
        PrivateKey
        import_k(boost::filesystem::path const& path,
                 elle::String const& passphrase =
                   cryptography::pem::defaults::passphrase,
                 Padding const encryption_padding =
                   defaults::encryption_padding,
                 Padding const signature_padding =
                   defaults::signature_padding,
                 Oneway const digest_algorithm =
                   defaults::digest_algorithm);
        /// Import an RSA key pair from a path.
        KeyPair
        import_keypair(boost::filesystem::path const& path,
                       elle::String const& passphrase =
                         cryptography::pem::defaults::passphrase,
                       Padding const encryption_padding =
                         defaults::encryption_padding,
                       Padding const signature_padding =
                         defaults::signature_padding,
                       Oneway const digest_algorithm =
                         defaults::digest_algorithm,
                       Cipher const envelope_cipher =
                         defaults::envelope_cipher,
                       Mode const envelope_mode =
                         defaults::envelope_mode);
        /// Export an RSA public key.
        void
        export_K(PublicKey const& K,
                 boost::filesystem::path const& path);
        /// Export an RSA private key, providing the passphrase, cipher and
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
        /// Export an RSA key pair.
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