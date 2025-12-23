#pragma once

#include <graphene/protocol/base.hpp>
#include <graphene/protocol/types.hpp>

namespace graphene { namespace protocol {

// Define a common template or macro for standard fee_parameters_type
// to reduce repetition. For brevity, a simple common struct is used here.
struct operation_fee_parameters {
    uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION;
};

// --- nft_lottery_token_purchase_operation ---

/**
 * @brief Operation to purchase tickets for an NFT lottery.
 */
struct nft_lottery_token_purchase_operation : public graphene::protocol::base_operation {
    using fee_parameters_type = operation_fee_parameters;

    asset fee;
    nft_metadata_id_type lottery_id;        // Lottery NFT Metadata
    account_id_type buyer;                  // Buyer purchasing lottery tickets
    uint64_t tickets_to_buy;                // Count of tickets to buy
    asset amount;                           // Amount that can be spent
    extensions_type extensions;

    account_id_type fee_payer() const {
        return buyer;
    }

    void validate() const; // Implementation expected elsewhere
    share_type calculate_fee(const fee_parameters_type& k) const; // Implementation expected elsewhere
};

// --- nft_lottery_reward_operation ---

/**
 * @brief Operation to reward a winner in an NFT lottery.
 */
struct nft_lottery_reward_operation : public graphene::protocol::base_operation  {
    using fee_parameters_type = operation_fee_parameters;

    asset fee;
    nft_metadata_id_type lottery_id;        // Lottery NFT Metadata
    account_id_type winner;                 // Winner account
    asset amount;                           // Amount won
    uint16_t win_percentage;                // Percentage of jackpot that user won
    bool is_benefactor_reward;              // True if received from benefactors section of lottery; false otherwise
    uint64_t winner_ticket_id;
    extensions_type extensions;

    // Fee paid by the system (not a specific account)
    account_id_type fee_payer() const {
        return account_id_type();
    }

    // Since this is a system operation, validation might be minimal/internal
    void validate() const {}
    share_type calculate_fee(const fee_parameters_type& k) const {
        return k.fee;
    }
};

// --- nft_lottery_end_operation ---

/**
 * @brief Operation to finalize and end an NFT lottery.
 */
struct nft_lottery_end_operation : public graphene::protocol::base_operation 
 {
    using fee_parameters_type = operation_fee_parameters;

    asset fee;
    nft_metadata_id_type lottery_id;
    extensions_type extensions;

    // Fee paid by the system
    account_id_type fee_payer() const {
        return account_id_type();
    }

    void validate() const {}
    share_type calculate_fee(const fee_parameters_type& k) const {
        return k.fee;
    }
};

} // namespace protocol
} // namespace graphene

// FC_REFLECT macros remain largely the same, but the fee parameter structs are consolidated.

FC_REFLECT(graphene::protocol::operation_fee_parameters, (fee))

FC_REFLECT(graphene::protocol::nft_lottery_token_purchase_operation,
           (fee)
           (lottery_id)
           (buyer)
           (tickets_to_buy)
           (amount)
           (extensions))

FC_REFLECT(graphene::protocol::nft_lottery_reward_operation,
           (fee)
           (lottery_id)
           (winner)
           (amount)
           (win_percentage)
           (is_benefactor_reward)
           (winner_ticket_id)
           (extensions))

FC_REFLECT(graphene::protocol::nft_lottery_end_operation,
           (fee)
           (lottery_id)
           (extensions))
