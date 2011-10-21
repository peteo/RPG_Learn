package org.photon.lib;

import java.util.Hashtable;
import java.util.Timer;
import java.util.TimerTask;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Binder;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;

import de.exitgames.client.photon.DebugLevel;
import de.exitgames.client.photon.IPhotonPeerListener;
import de.exitgames.client.photon.LiteEventCode;
import de.exitgames.client.photon.LiteEventKey;
import de.exitgames.client.photon.LiteOpCode;
import de.exitgames.client.photon.LiteOpKey;
import de.exitgames.client.photon.LitePeer;
import de.exitgames.client.photon.PhotonPeer;
import de.exitgames.client.photon.StatusCode;

import org.photon.lib.SettingsData;

public class PhotonHelper extends Service implements IPhotonPeerListener
{
	static SettingsData settings;
	private static LitePeer peer;
	private static Timer timer;
	
	private static long lastRandomMoveTime = 0xFFFFFFFF;
	private static long lastSendTime = 0xFFFFFFFF;
	private static long lastDispatchTime = 0xFFFFFFFF;
	private static long startTime;
	
	private static Integer	eventCounter = 0;

	public static int NonConsecutiveIssueCount;
	
	/**
     * Class for clients to access.  Because we know this service always
     * runs in the same process as its clients, we don't need to deal with
     * IPC.
     */
    public class LocalBinder extends Binder 
    {
    	PhotonHelper getService() 
    	{
            return PhotonHelper.this;
        }
    }
    
    public PhotonHelper()
    {
    	settings = new SettingsData();
		
		peer = new LitePeer(this, settings.useTcp);
	}
    
    @Override
	public void onCreate()
	{
		super.onCreate();
	}
	
	@Override
	public void onDestroy()
	{
		super.onDestroy();
		disconnect();
	}
	
	@Override
	public IBinder onBind(Intent arg0) 
	{
		return mBinder;
	}
	
	private final IBinder mBinder = new LocalBinder();
	
	public void debugReturn(DebugLevel level, String message)
	{
		Log.d("CLIENT", message);
	}
	
	public static void printHasptable(Hashtable<Object, Object> hashtable)
	{
		/*
	    Set<String> keys = hashtable.keySet();
	    for(String key: keys) 
	    {
	    	System.out.println(key+"--"+hashtable.get(key));
	    }
	    */
	}

	public void eventAction(final byte eventCode, final Hashtable<Byte, Object> ev)  
	{
		
	}

	public void operationResult(byte opCode, int returnCode,
			Hashtable<Byte, Object> returnValues, short invocID) 
	{
		switch(opCode)
		{
		case LiteOpCode.Join:
			Log.d("CLIENT", "join result: "+returnCode);
			break;
		case LiteOpCode.ExchangeKeysForEncryption:
			this.debugReturn(DebugLevel.INFO, "OpExchangeKeysForEncryption response: " + returnValues.toString());
            
			this.peer.deriveSharedKey((byte[])returnValues.get((byte)LiteOpKey.ServerKey.value()));
            this.debugReturn(DebugLevel.INFO, "IsEncryptionAvailable(): " + this.peer.isEncryptionAvailable());
            
            peer.opJoin(settings.gameName);
			break;
		}
	}

	public void peerStatusCallback(StatusCode statusCode) 
	{
		String message;
		
		switch (statusCode)
		{
		case Connect:
			//peer.opExchangeKeysForEncryption();
			Log.d("peerStatusCallback","Connected");
			break;
		case Disconnect:
			Log.d("peerStatusCallback","Disconnected");
			break;
        case Exception_Connect:
        	message = "Exception_Connect(ed) peer.state: " + peer.getPeerState();
        	debugReturn(DebugLevel.ERROR, message);
            break;
        case Exception:
        	message = "Exception peer.state: " + peer.getPeerState();
        	debugReturn(DebugLevel.ERROR, message);
            break;
        case SendError:
        	message = "SendError! peer.state: " + peer.getPeerState();
        	debugReturn(DebugLevel.ERROR, message);
            break;
        case TimeoutDisconnect:
        	message = "TimeoutDisconnect! peer.state: " + peer.getPeerState();
        	debugReturn(DebugLevel.ERROR, message);
            break;
        default:
        	message = "PeerStatusCallback: " + statusCode;
        	debugReturn(DebugLevel.ERROR, message);
            break;
		}
	}
	
	
	public static void connect()
	{
		Log.d("connect","222222222222222222222222222222222222");
		
		peer.connect(settings.server, "MmoDemo");
		
		startTime = System.currentTimeMillis();
		
		Log.d("connect","333333333333333333333333333333333333");
		
		//test
		
		
		timer = new Timer("main loop");
		TimerTask timerTask = new TimerTask()
		{
			public void run()
			{
				if (null == peer)
				{
					cancel();
					timer.cancel();
					
					return;
				}
				
				if (peer.getPeerState() == PhotonPeer.PS_CONNECTED)
				{
					if ( (System.currentTimeMillis() - lastRandomMoveTime) > settings.randomMoveInterval)
					{
						lastRandomMoveTime = System.currentTimeMillis();
					}
				}
					
				// to spare some overhead, we will send outgoing packets in certain intervals, as defined
				// in the settings menu. 				
				if ( (System.currentTimeMillis() - lastSendTime) > settings.intervalSend)
				{
					lastSendTime = System.currentTimeMillis();
					peer.sendOutgoingCommands();					
				}
				
				// test if it's time to dispatch all incoming commands to the application. Dispatching
				// will empty the queue of incoming messages and will fire the related callbacks.
				if ( (System.currentTimeMillis() - lastDispatchTime) > settings.intervalDispatch)
				{
					lastDispatchTime = System.currentTimeMillis();
					
					// dispatch all incoming commands
					while (peer.dispatchIncomingCommands()) {};
				}
			}
		};
		
		timer.schedule(timerTask, 0, 5);
		
	}
		
	public void disconnect()
	{
		if (null != timer)
		{
			timer.cancel();
			timer = null;
		}
		
		if (null != peer)
		{
			peer. opLeave(settings.gameName);
			peer.disconnect();
		}
		
		peer = null;
	}
}
