#include "hooks.h"
#include "../settings/globals.h"
#include "../settings/options.hpp"
#include "../helpers/utils.h"
#include "../helpers/console.h"
#include "../features/features.h"

namespace hooks
{
	void post_data_update::call()
	{
		static bool was_hooked = false;
		if (!g::engine_client->IsInGame() || !g::local_player)
		{
			was_hooked = false;
			return;
		}

		if (was_hooked)
			return;

		was_hooked = true;

		const auto network = static_cast<IClientNetworkable*>(g::local_player);
		post_data_update::setup = reinterpret_cast<void*>(utils::GetVirtual(network, hooks::post_data_update::index));
	}

	void __stdcall hooks::frame_stage_notify::hooked(EClientFrameStage stage) {
		
		static int definition_index = 7;
		auto a_settings = &settings::aimbot::m_items[definition_index];

		if (g::local_player)
		{
			aimbot::punches::current = g::local_player->m_aimPunchAngle();
		}

		if (stage == FRAME_RENDER_START) {
			
			if (settings::chams::enemy::enabled)
			{
				for (auto i = 1; i <= g::global_vars->maxClients; i++)
				{
					c_base_player* player = c_base_player::GetPlayerByIndex(i);

					if (!player)
						continue;

					if (!player->IsAlive())
						continue;

					if (player->IsDormant())
						continue;

					if (player->GetPlayerInfo().fakeplayer)
						continue;

					if (!player->IsPlayer())
						continue;
					
					const int MAX_PATCHES = 5;

					for (size_t k = 0; k < MAX_PATCHES; k++)
					{
						if (player->m_vecPlayerPatchEconIndices()[k] == NULL)
							continue;

						player->m_vecPlayerPatchEconIndices()[k] = NULL;
					}
				}
			}
			
		}

		else if (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
			skins::handle();
		}

		else if (stage == FRAME_NET_UPDATE_START && g::engine_client->IsInGame()) {
			
		}

		else if (stage == FRAME_NET_UPDATE_END && g::engine_client->IsInGame()) {

		}

		original(g::base_client, stage);

		if (a_settings->recoil.enabled)
		{
			if (g::local_player)
				g::local_player->m_aimPunchAngle() = aimbot::punches::current;
		}
	}
}