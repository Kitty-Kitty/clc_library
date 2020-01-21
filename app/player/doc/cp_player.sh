#! /bin/bash
#

# See how we were called.
case "$1" in
  start)
	export CP_ENV_CONF_PATH="/opt/cp_player/configs/css.conf"
	export CP_ENV_DAEMON_MODE=""
	
	sudo -i rm -f /opt/cp_player/configs/cp_app_pid
	sudo -i /opt/cp_player/cp_player
        ;;
  stop)
	kill -9 `sudo cat /opt/cp_player/configs/cp_app_pid`
        ;;
  status)
	;;
  restart|reload|force-reload)
	;;
  *)
        echo $"Usage: $0 {start|stop|status|restart|reload|force-reload}"
        exit 2
esac

exit $rc
