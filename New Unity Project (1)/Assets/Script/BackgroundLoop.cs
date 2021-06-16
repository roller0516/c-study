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
        width = backGroundCollider.size.x;

    }
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (transform.position.x <= -width) 
        {
            RePosition();
        }

    }
    void RePosition() 
    {
        Vector3 offset = new Vector3(100, -0.2f, -0.9f);
        transform.position = offset;
    }
}
