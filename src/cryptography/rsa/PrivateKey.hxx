#ifndef INFINIT_CRYPTOGRAPHY_RSA_PRIVATEKEY_HXX
# define INFINIT_CRYPTOGRAPHY_RSA_PRIVATEKEY_HXX

# if defined(INFINIT_CRYPTOGRAPHY_LEGACY)

#  include <cryptography/serialization.hh>
#  include <cryptography/Cryptosystem.hh>
#  include <cryptography/Error.hh>
#  include <cryptography/hash.hh>
#  include <cryptography/context.hh>
#  include <cryptography/_legacy/envelope.hh>
#  include <cryptography/_legacy/Clear.hh>

#  include <elle/Buffer.hh>
#  include <elle/log.hh>

#  include <openssl/err.h>

namespace infinit
{
  namespace cryptography
  {
    namespace rsa
    {
      /*--------.
      | Methods |
      `--------*/

      template <typename T>
      T
      PrivateKey::decrypt(Code const& code) const
      {
        ELLE_LOG_COMPONENT("infinit.cryptography.rsa.PrivateKey");
        ELLE_TRACE_METHOD("");
        ELLE_DUMP("code: %x", code);

        types::EVP_PKEY_CTX context(
          context::create(this->_key.get(), ::EVP_PKEY_decrypt_init));
        padding::pad(context.get(), this->_encryption_padding);

        Clear clear(envelope::open(code.buffer(),
                                   context.get(),
                                   ::EVP_PKEY_decrypt));

        return (cryptography::deserialize<T>(clear.buffer()));
      }

      template <typename T>
      Signature
      PrivateKey::sign(T const& value) const
      {
        ELLE_LOG_COMPONENT("infinit.cryptography.rsa.PrivateKey");
        ELLE_TRACE_METHOD("");
        ELLE_DUMP("value: %x", value);

        static_assert(std::is_same<T, Digest>::value == false,
                      "this call should never have occured");

        elle::Buffer _value = cryptography::serialize(value);

        elle::IOStream _plain(_value.istreambuf());

        return (Signature(this->sign(static_cast<std::istream&>(_plain),
                                     this->_signature_padding,
                                     this->_oneway)));
      }
    }
  }
}

/*-------------.
| Serializable |
`-------------*/

#  include <elle/serialize/Serializer.hh>
#  include <elle/serialize/StaticFormat.hh>

#  include <cryptography/finally.hh>
#  include <cryptography/rsa/der.hh>
#  include <cryptography/_legacy/rsa.hh>

ELLE_SERIALIZE_STATIC_FORMAT(infinit::cryptography::rsa::PrivateKey, 1);

ELLE_SERIALIZE_SPLIT(infinit::cryptography::rsa::PrivateKey)

ELLE_SERIALIZE_SPLIT_SAVE(infinit::cryptography::rsa::PrivateKey,
                          archive,
                          value,
                          format)
{
  // Since the original class was the parent PrivateKey class that was
  // always in format 0, we can enforce the format's value.
  enforce(format == 0);

  archive << infinit::cryptography::Cryptosystem::rsa;

  // Create the subclass (i.e originally rsa::PrivateKey) and set the
  // format to the right value.
  infinit::cryptography::legacy::rsa::Dummy implementation;
  auto& _implementation_dynamic_format =
    static_cast<
      elle::serialize::DynamicFormat<
        infinit::cryptography::legacy::rsa::Dummy>&>(implementation);
  _implementation_dynamic_format.version(value._legacy_format);
  archive << implementation;

  switch (format)
  {
    case 0:
    case 1:
    {
      archive << *value._key->pkey.rsa->n
              << *value._key->pkey.rsa->e
              << *value._key->pkey.rsa->d
              << *value._key->pkey.rsa->p
              << *value._key->pkey.rsa->q
              << *value._key->pkey.rsa->dmp1
              << *value._key->pkey.rsa->dmq1
              << *value._key->pkey.rsa->iqmp;

      break;
    }
    default:
      throw infinit::cryptography::Error(
        elle::sprintf("unknown format '%s'", value._legacy_format));
  }
}

ELLE_SERIALIZE_SPLIT_LOAD(infinit::cryptography::rsa::PrivateKey,
                          archive,
                          value,
                          format)
{
  // Emulate deserializing the parent class. Please see PrivateKey.hxx
  // for more information.
  enforce(format == 0);

  // Extract the cryptosystem which was in the parent class PrivateKey.
  infinit::cryptography::Cryptosystem cryptosystem;
  archive >> cryptosystem;
  ELLE_ASSERT_EQ(cryptosystem, infinit::cryptography::Cryptosystem::rsa);

  // Extract the subclass: rsa::PrivateKey.
  infinit::cryptography::legacy::rsa::Dummy implementation;
  archive >> implementation;

  // Report the subclass' format in the current one since the modern
  // rsa::PrivateKey class plays the role of both classes.
  auto& _implementation_dynamic_format =
    static_cast<
      elle::serialize::DynamicFormat<
        infinit::cryptography::legacy::rsa::Dummy>&>(implementation);
  value._legacy_format = _implementation_dynamic_format.version();

  switch (value._legacy_format)
  {
    case 0:
    case 1:
    {
      // Extract the big numbers.
      ::BIGNUM *n = ::BN_new();
      ::BIGNUM *e = ::BN_new();
      ::BIGNUM *d = ::BN_new();
      ::BIGNUM *p = ::BN_new();
      ::BIGNUM *q = ::BN_new();
      ::BIGNUM *dmp1 = ::BN_new();
      ::BIGNUM *dmq1 = ::BN_new();
      ::BIGNUM *iqmp = ::BN_new();

      ELLE_ASSERT_NEQ(n, nullptr);
      ELLE_ASSERT_NEQ(e, nullptr);
      ELLE_ASSERT_NEQ(d, nullptr);
      ELLE_ASSERT_NEQ(p, nullptr);
      ELLE_ASSERT_NEQ(q, nullptr);
      ELLE_ASSERT_NEQ(dmp1, nullptr);
      ELLE_ASSERT_NEQ(dmq1, nullptr);
      ELLE_ASSERT_NEQ(iqmp, nullptr);

      INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_BN(n);
      INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_BN(e);
      INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_BN(d);
      INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_BN(p);
      INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_BN(q);
      INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_BN(dmp1);
      INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_BN(dmq1);
      INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_BN(iqmp);

      archive >> *n
              >> *e
              >> *d
              >> *p
              >> *q
              >> *dmp1
              >> *dmq1
              >> *iqmp;

      // Build the RSA object.
      ::RSA* rsa = ::RSA_new();

      ELLE_ASSERT_NEQ(rsa, nullptr);

      INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_RSA(rsa);

      rsa->n = n;
      rsa->e = e;
      rsa->d = d;
      rsa->p = p;
      rsa->q = q;
      rsa->dmp1 = dmp1;
      rsa->dmq1 = dmq1;
      rsa->iqmp = iqmp;

      INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(n);
      INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(e);
      INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(d);
      INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(p);
      INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(q);
      INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(dmp1);
      INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(dmq1);
      INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(iqmp);

      // Set the default configuration values.
      switch (value._legacy_format)
      {
        case 0:
        {
          value._encryption_padding =
            infinit::cryptography::rsa::Padding::oaep;
          value._signature_padding =
            infinit::cryptography::rsa::Padding::pkcs1;
          value._oneway =
            infinit::cryptography::Oneway::sha256;
          value._envelope_cipher =
            infinit::cryptography::Cipher::aes256;
          value._envelope_mode =
            infinit::cryptography::Mode::cbc;

          break;
        }
        case 1:
        {
          value._encryption_padding =
            infinit::cryptography::rsa::Padding::pkcs1;
          value._signature_padding =
            infinit::cryptography::rsa::Padding::pkcs1;
          value._oneway =
            infinit::cryptography::Oneway::sha256;
          value._envelope_cipher =
            infinit::cryptography::Cipher::aes256;
          value._envelope_mode =
            infinit::cryptography::Mode::cbc;

          break;
        }
        default:
          unreachable();
      }

      // Construct and prepare the final object.
      value._construct(rsa);

      INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(rsa);

      value._check();

      break;
    }
    default:
      throw infinit::cryptography::Error(
        elle::sprintf("unknown format '%s'", value._legacy_format));
  }
}

# else

#  include <elle/serialization/binary.hh>
#  include <elle/utility/Move.hh>

namespace infinit
{
  namespace cryptography
  {
    namespace rsa
    {
      template <typename T>
      elle::Buffer
      PrivateKey::sign(T const& o) const
      {
        return this->sign(
          o,
          elle::serialization::_details::serialization_tag<T>::type::version);
      }

      template <>
      inline
      elle::Buffer
      PrivateKey::sign<elle::Buffer>(elle::Buffer const& b) const
      {
        return this->sign(elle::ConstWeakBuffer(b));
      }

      template <typename T>
      elle::Buffer
      PrivateKey::sign(T const& o, elle::Version const& version) const
      {
        return this->_sign_async(o, version)(this);
      }

      template <typename T>
      std::function<elle::Buffer ()>
      PrivateKey::sign_async(T const& o, elle::Version const& version) const
      {
        return [self = this->shared_from_this(),
                sign = this->_sign_async(o, version)]
        {
          return sign(self.get());
        };
      }

      template <typename T>
      std::function<elle::Buffer (PrivateKey const* self)>
      PrivateKey::_sign_async(T const& o, elle::Version const& version) const
      {
        ELLE_LOG_COMPONENT("infinit.cryptography.rsa.PrivateKey");
        ELLE_TRACE_SCOPE("%s: sign %s", *this, o);
        return [serialized =
                  elle::serialization::binary::serialize(o, version, false),
                version] (PrivateKey const* self)
        {
          elle::Buffer res;
          {
            elle::IOStream output(res.ostreambuf());
            elle::serialization::binary::serialize(version, output, false);
            ELLE_DUMP("serialization: %s", serialized);
            auto signature = self->sign(serialized);
            ELLE_DUMP("signature: %s", signature);
            ELLE_DUMP("version: %s", version);
            output.write(reinterpret_cast<char const*>(signature.contents()),
                         signature.size());
          }
          return res;
        };
      }
    }
  }
}

# endif

//
// ---------- Hash ------------------------------------------------------------
//

# include <elle/serialization/binary.hh>

namespace std
{
  template <>
  struct hash<infinit::cryptography::rsa::PrivateKey>
  {
    size_t
    operator ()(infinit::cryptography::rsa::PrivateKey const& value) const
    {
      std::stringstream stream;
      {
        elle::serialization::binary::SerializerOut output(stream);
        output.serialize("value", value);
      }

      size_t result = std::hash<std::string>()(stream.str());

      return (result);
    }
  };
}

#endif
