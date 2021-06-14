using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMove : MonoBehaviour
{
    public Player player;
    [SerializeField]
    float x, y, z;
    float angle;

    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        this.transform.position = new Vector3(player.transform.position.x + x, player.transform.position.y + y, player.transform.position.z + z);
        transform.LookAt(player.transform);
    }
}
