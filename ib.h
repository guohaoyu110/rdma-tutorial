#ifndef IB_H_
#define IB_H_

#include <arpa/inet.h>
#include <byteswap.h>
#include <endian.h>
#include <infiniband/verbs.h>
#include <inttypes.h>
#include <sys/types.h>

#define IB_MTU IBV_MTU_4096
#define IB_PORT 1
#define IB_SL 0
#define IB_WR_ID_STOP 0xE000000000000000
#define NUM_WARMING_UP_OPS 500000
#define TOT_NUM_OPS 10000000
#define SIG_INTERVAL 1000

#if __BYTE_ORDER == __LITTLE_ENDIAN
static inline uint64_t htonll(uint64_t x) { return bswap_64(x); }
static inline uint64_t ntohll(uint64_t x) { return bswap_64(x); }
#elif __BYTE_ORDER == __BIG_ENDIAN
static inline uint64_t htonll(uint64_t x) { return x; }
static inline uint64_t ntohll(uint64_t x) { return x; }
#else
#error __BYTE_ORDER is neither __LITTLE_ENDIAN nor __BIG_ENDIAN
#endif

struct qp_info {
    uint16_t lid;
    uint32_t qp_num;
    uint32_t rank;
} __attribute__((packed));

enum MSG_TYPE {
    MSG_CTL_START = 100,
    MSG_CTL_STOP,
};

int modify_qp_to_rts(struct ibv_qp *qp, uint32_t qp_num, uint16_t lid);

int post_send(uint32_t req_size, uint32_t lkey, uint64_t wr_id,
              uint32_t imm_data, struct ibv_qp *qp, char *buf);

int post_srq_recv(uint32_t req_size, uint32_t lkey, uint64_t wr_id,
                  struct ibv_srq *srq, char *buf);

#endif /*ib.h*/
