.PHONY: all clean fclean re mre

CLIENT := client
SERVER := server

CLIENT_PATH := clientDir/
SERVER_PATH := serverDir/

all:
	@ make -C $(CLIENT_PATH)
	@ make -C $(SERVER_PATH)
	@ ln -fs $(CLIENT_PATH)$(CLIENT) $(CLIENT)
	@ ln -fs $(SERVER_PATH)$(SERVER) $(SERVER)
	@ chmod 744 $(CLIENT) $(SERVER)

mre:
	@ make mre -C $(CLIENT_PATH)
	@ make mre -C $(SERVER_PATH)
	@ ln -fs $(CLIENT_PATH)$(CLIENT) $(CLIENT)
	@ ln -fs $(SERVER_PATH)$(SERVER) $(SERVER)
	@ chmod 744 $(CLIENT) $(SERVER)

clean:
	make clean -C $(CLIENT_PATH)
	make clean -C $(SERVER_PATH)

fclean:
	make fclean -C $(CLIENT_PATH)
	make fclean -C $(SERVER_PATH)
	rm -f $(CLIENT) $(SERVER)

re: fclean all
