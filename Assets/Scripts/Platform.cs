using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Platform : MonoBehaviour
{
    bool isStepped = false;

    private void OnEnable()
    {
        isStepped = false;
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Player" && !isStepped)
        {
            isStepped = true;

            //AutoDissolve[] autoDissolves = GetComponentsInChildren<AutoDissolve>();
            //foreach(AutoDissolve dissolve in autoDissolves)
            //{
            //    dissolve.isDissolve = true;
            //}
        }
    }
}
