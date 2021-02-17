/* -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2012-2021 University of California, Los Angeles
 *
 * This file is part of ndn-svs, synchronization library for distributed realtime
 * applications for NDN.
 *
 * ndn-svs library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, in version 2.1 of the License.
 *
 * ndn-svs library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 */

#ifndef NDN_SVS_SOCKET_MULTICAST_HPP
#define NDN_SVS_SOCKET_MULTICAST_HPP

#include "socket-base.hpp"

namespace ndn {
namespace svs {

/**
 * @brief Socket using multicast for data delivery
 *
 * Sync logic runs under <base-prefix>/s
 * Data is produced as <base-prefix>/d/<node-id>/<seq>
 */
class SocketMulticast : public SocketBase
{
public:
  SocketMulticast(const Name& basePrefix,
         const NodeID& id,
         ndn::Face& face,
         const UpdateCallback& updateCallback,
         const std::string& syncKey = Logic::DEFAULT_SYNC_KEY,
         const Name& signingId = DEFAULT_NAME,
         std::shared_ptr<Validator> validator = DEFAULT_VALIDATOR,
         std::shared_ptr<DataStore> dataStore = DEFAULT_DATASTORE)
  : SocketBase(
      Name(m_basePrefix).append("s"),
      Name(m_basePrefix).append("d"),
      id, face, updateCallback, syncKey, signingId, validator, dataStore)
  , m_basePrefix(basePrefix)
  {}

  inline Name
  getDataName(const NodeID& nid, const SeqNo& seqNo)
  {
    return Name(m_dataPrefix).append(nid).appendNumber(seqNo);
  }

  /*** @brief Set whether data of other nodes is also cached and served */
  void
  setCacheAll(bool val)
  {
    m_cacheAll = val;
  }

private:
  bool
  shouldCache(const Data& data)
  {
    return m_cacheAll;
  }

private:
  const Name m_basePrefix;
  bool m_cacheAll = false;
};

}  // namespace svs
}  // namespace ndn

#endif // NDN_SVS_SOCKET_MULTICAST_HPP
