#if defined(INFINIT_CRYPTOGRAPHY_LEGACY)
# ifndef INFINIT_CRYPTOGRAPHY_LEGACY_SERIALIZATION_HXX
#  define INFINIT_CRYPTOGRAPHY_LEGACY_SERIALIZATION_HXX

#  include <cryptography/_legacy/Plain.hh>

#  include <elle/serialize/BaseArchive.hxx>

#  include <elle/Buffer.hh>
#  include <elle/log.hh>

namespace infinit
{
  namespace cryptography
  {
    /*----------.
    | Functions |
    `----------*/

    template <typename T>
    elle::Buffer
    serialize(T const& value)
    {
      ELLE_LOG_COMPONENT("infinit.cryptography.legacy");
      ELLE_DEBUG_FUNCTION("T");
      ELLE_DUMP("value: %x", value);

      static_assert(std::is_same<T, Plain>::value == false,
                    "this call should never have occured");
      static_assert(std::is_same<T, elle::Buffer>::value == false,
                    "this call should never have occured");
      static_assert(std::is_same<T, elle::WeakBuffer>::value == false,
                    "this call should never have occured");
      static_assert(std::is_same<T, elle::ConstWeakBuffer>::value == false,
                    "this call should never have occured");

      elle::Buffer archive;
      archive.writer() << value;

      return (archive);
    }

    template <typename T>
    T
    deserialize(elle::ConstWeakBuffer const& archive)
    {
      ELLE_LOG_COMPONENT("infinit.cryptography.legacy");
      ELLE_DEBUG_FUNCTION("T");
      ELLE_DUMP("archive: %x", archive);

      static_assert(std::is_same<T, Clear>::value == false,
                    "this call should never have occured");
      static_assert(std::is_same<T, elle::Buffer>::value == false,
                    "this call should never have occured");
      static_assert(std::is_same<T, elle::WeakBuffer>::value == false,
                    "this call should never have occured");
      static_assert(std::is_same<T, elle::ConstWeakBuffer>::value == false,
                    "this call should never have occured");

      T value;
      archive.reader() >> value;

      return (value);
    }
  }
}
# endif

#else
# warning "LEGACY: this file should not have been included"
#endif
