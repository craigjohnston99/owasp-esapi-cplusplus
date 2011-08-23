/**
* OWASP Enterprise Security API (ESAPI)
*
* This file is part of the Open Web Application Security Project (OWASP)
* Enterprise Security API (ESAPI) project. For details, please see
* http://www.owasp.org/index.php/ESAPI.
*
* Copyright (c) 2011 - The OWASP Foundation
*
* @author Kevin Wall, kevin.w.wall@gmail.com
* @author Jeffrey Walton, noloader@gmail.com
*
*/

#include "crypto/RandomPool.h"
#include "crypto/Crypto++Common.h"
#include "util/ArrayZeroizer.h"
#include "errors/EncryptionException.h"
#include "errors/InvalidArgumentException.h"

#include <time.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/random.h>

namespace esapi
{
  class AutoFileDesc
  {
  public:
    explicit AutoFileDesc(int& fd) : m_fd(fd) { }

    ~AutoFileDesc() {
      if(m_fd)
        close(m_fd);
      m_fd = NULL;
    }

  private:
    int m_fd;
  };

  static __inline__ unsigned long long rdtsc(void)
  {
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
  }

  bool RandomPool::GenerateKey(byte* key, size_t ksize)
  {
    ASSERT(key && ksize);
    if(!key || !ksize) return false;

    size_t rem = ksize;
    size_t idx = 0;

    // First try the random pool
    {
      do
      {
        int fd = open("/dev/random", O_RDONLY);
        AutoFileDesc z1(fd);

        ASSERT(fd > 0);
        if( !(fd > 0) ) break; /* Failed */

        do
        {
          struct rand_pool_info info;
          int ret = ioctl(fd, RNDGETENTCNT, &info);
          ASSERT(ret >= 0);
          if( !(ret >= 0) ) break; /* Failed */

          if(info.entropy_count < 128) break; /* Failed (would block) */

          static const size_t Chunk = 8;
          const size_t req = std::min(rem, Chunk);

          CryptoPP::Timer timer;
          timer.StartTimer();

          ret = read(fd, key+idx, req);
          ASSERT(ret >= 0);
          if( !(ret >= 0) ) break; /* Failed */

          // The return value determine bytes read
          rem -= ret;
          idx += ret;

          // If it appears we have read too little or blocked, break and fall back /dev/urandom
          if(req != (unsigned int)ret || timer.ElapsedTime() > 1) break;

        } while(rem > 0);

      } while(false);
    }

    // Early out if possible.
    if(rem == 0) return true;

    // Next try urandom
    {
      do
      {
        int fd = open("/dev/urandom", O_RDONLY);
        AutoFileDesc z1(fd);

        ASSERT(fd > 0);
        if( !(fd > 0) ) break; /* Failed */

        int ret = read(fd, key+idx, rem);
        ASSERT(ret >= 0);
        if( !(ret >= 0) ) break; /* Failed */

      } while(false);
    }

    return (rem == 0);
  }

  bool RandomPool::GetTimeData(byte* data, size_t dsize)
  {
    ASSERT(data && dsize);
    if(!data || !dsize) return false;

    size_t idx = 0, rem = dsize, req = 0;

    unsigned long long ts = rdtsc();

    req = std::min(rem, sizeof(ts));
    ::memcpy(data, &ts, req);
    rem -= req; idx+= req;

    // Any room remaining? There should be...
    if(!rem) return true;

    time_t now;
    time(&now);

    req = std::min(rem, sizeof(now));
    ::memcpy(data+idx, &now, req);

    return true;
  }
}
