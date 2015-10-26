#ifndef INFINIT_CRYPTOGRAPHY_RANDOM_HH
# define INFINIT_CRYPTOGRAPHY_RANDOM_HH

# include <elle/types.hh>

namespace infinit
{
  namespace cryptography
  {
    /// Provide functionalities for generating random values.
    namespace random
    {
      /*----------.
      | Functions |
      `----------*/

      /// Generate a random value. The following versions are provided:
      ///
      ///   generate<elle::Boolean>();
      ///   generate<elle::Character>();
      ///   generate<elle::Character>(elle::Character minimum,
      ///                             elle::Character maximum);
      ///   generate<elle::Real>();
      ///   generate<int8_t>();
      ///   generate<int8_t>(int8_t minimum,
      ///                    int8_t maximum);
      ///   generate<int16_t>();
      ///   generate<int16_t>(int16_t minimum,
      ///                     int16_t maximum);
      ///   generate<int32_t>();
      ///   generate<int32_t>(int32_t minimum,
      ///                     int32_t maximum);
      ///   generate<elle::Integer64>();
      ///   generate<elle::Integer64>(elle::Integer64 minimum,
      ///                             elle::Integer64 maximum);
      ///   generate<elle::Natural8>();
      ///   generate<elle::Natural8>(elle::Natural8 minimum,
      ///                            elle::Natural8 maximum);
      ///   generate<elle::Natural16>();
      ///   generate<elle::Natural16>(elle::Natural16 minimum,
      ///                             elle::Natural16 maximum);
      ///   generate<elle::Natural32>();
      ///   generate<elle::Natural32>(elle::Natural32 minimum,
      ///                             elle::Natural32 maximum);
      ///   generate<elle::Natural64>();
      ///   generate<elle::Natural64>(elle::Natural64 minimum,
      ///                             elle::Natural64 maximum);
      ///   generate<elle::String>(elle::Natural32 length);
      ///   generate<elle::Buffer>(elle::Natural32 size);
      template <typename T,
                typename... A>
      T
      generate(A... arguments);
      /// Fill a buffer with random bytes. See RAND_bytes.
      void
      fill(unsigned char* buffer,
           size_t const size);
      /// Set up the random generator by adding entropy.
      ///
      /// !WARNING! Do not use unless you know exactly what you're doing.
      void
      setup();
    }
  }
}

# include <cryptography/random.hxx>

#endif
