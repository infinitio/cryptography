#ifndef  ELLE_CRYPTOGRAPHY_SEED_HXX
# define ELLE_CRYPTOGRAPHY_SEED_HXX

# include <cassert>

# include <elle/serialize/ArchiveSerializer.hxx>

# include <elle/cryptography/Seed.hh>

ELLE_SERIALIZE_SIMPLE(elle::cryptography::Seed,
                      archive,
                      value,
                      version)
{
  assert(version == 0);
  archive & value.region;
}

#endif