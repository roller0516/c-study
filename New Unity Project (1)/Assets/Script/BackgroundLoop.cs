using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackgroundLoop : MonoBehaviour
{
    // Start is called before the first frame update
    float width;
    private void Awake()
    {
        BoxCollider backGroundCollider = GetComponent<BoxCollider>();
        width = backGroundCollider.size.x*100;

    }
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (this.transform.position.x <= -width) 
        {
            RePosition();
        }

    }
    void RePosition() 
    {
        Vector3 offset = new Vector3(width*2f-1,0,0);
        this.transform.position = (Vector3)this.transform.position +offset;
    }
}
