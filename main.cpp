#include <iostream>
#include <dpp/dpp.h>

dpp::message message;
std::string BOT_TOKEN = std::getenv("BOT_TOKEN");
unsigned long long CHANNEL_ID = std::stoll(std::getenv("CHANNEL_ID"));

int main() {
    dpp::cluster bot(BOT_TOKEN);
   
    bot.on_log(dpp::utility::cout_logger());

    bot.on_ready([&bot](const dpp::ready_t& event) {
		// Lets send a message that the bot is operational
        message = dpp::message(dpp::snowflake(CHANNEL_ID), "");
        message.add_embed(dpp::embed().set_color(dpp::colors::green).set_title("SYSTEM IS OPERATIONAL!").set_timestamp(std::time(nullptr)));
        bot.message_create_sync(message);
		
        while (true) {
			std::this_thread::sleep_for(std::chrono::minutes(5));
            message.embeds[0].set_timestamp(std::time(nullptr));
        }
    });

    bot.start(false);
}